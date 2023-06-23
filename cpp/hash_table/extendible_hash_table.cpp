#include <bitset>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <list>
#include <utility>


#include "extendible_hash_table.h"



template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(size_t bucket_size)
    : global_depth_(0), bucket_size_(bucket_size), num_buckets_(1 << global_depth_) {
  dir_.resize(num_buckets_);
  for (int i = 0; i < num_buckets_; i++) {
    dir_[i] = std::make_shared<Bucket>(bucket_size_, global_depth_);
  }
}

template <typename K, typename V>
template <typename InputIt>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(InputIt first, InputIt last, size_t bucket_size) :
   ExtendibleHashTable(bucket_size) {
   for (auto iter = first; iter != last; ++iter) {
      insert(iter->first, iter->second);
   }
}

template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(std::initializer_list<ElementType> init, size_t bucket_size) :
   ExtendibleHashTable{init.begin(), init.end(), bucket_size} {
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::indexOf(const K &key) -> size_t {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  int mask = (1 << global_depth_) - 1;
  return std::hash<K>()(key) & mask;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::getGlobalDepth() const -> int {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  return global_depth_;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::getLocalDepth(int dir_index) const -> int {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  return dir_[dir_index]->getDepth();
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::getNumBuckets() const -> int {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  return num_buckets_;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::find(const K &key) -> EXTENDIBLE_HASH_TABLE_TYPE::Iterator {
  std::shared_lock<std::shared_mutex> lock(mutex_);
  size_t bucket_index = indexOf(key);
  Node *node = dir_[bucket_index]->find(key);

  if(node == nullptr){
    return end();
  }

  return Iterator(&dir_, bucket_index, node);
  
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::remove(const K &key) -> bool {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  Iterator pos = find(key);
  if(pos == end()){
    return false;
  }
  remove(pos);
  return true;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::remove(EXTENDIBLE_HASH_TABLE_TYPE::Iterator pos) -> EXTENDIBLE_HASH_TABLE_TYPE::Iterator {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  std::shared_ptr<Bucket> bucket = dir_[pos.bucket_index_];
  bucket->remove(pos++.node_);
  return pos;
}



template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::insert(const K &key, const V &value) -> std::pair<EXTENDIBLE_HASH_TABLE_TYPE::Iterator, bool> {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  int old_num_buckets_ = num_buckets_;
  // std::cout << "insert(" << key <<"," << value << ")"<< std::endl;
  std::shared_ptr<Bucket> bucket = dir_[indexOf(key)];
  if (bucket->isFull()) {
    if (bucket->getDepth() == global_depth_) {
      int high_bit = 1 << global_depth_;
      num_buckets_ *= 2;
      global_depth_++;
      dir_.resize(num_buckets_);
      for (int i = 0; i < old_num_buckets_; i++) {
        // LOG_DEBUG("%d, %d, %d, %d\n", i, high_bit, i + high_bit, num_buckets_);
        dir_[i + high_bit] = dir_[i];
      }
    }

    std::shared_ptr<Bucket> bucket0 = std::make_shared<Bucket>(bucket_size_, bucket->getDepth() + 1);
    std::shared_ptr<Bucket> bucket1 = std::make_shared<Bucket>(bucket_size_, bucket->getDepth() + 1);
    int local_hight_bit = 1 << (bucket->getDepth());
    for(Node *node = bucket->list_; node != nullptr; node = node->next){
      std::shared_ptr<Bucket> new_buket = (std::hash<K>()(node->value.first) & local_hight_bit) == 0 ? bucket0 : bucket1;
      new_buket->insert(node->value.first, node->value.second);
    }

    for (int i = std::hash<K>()(key) & (local_hight_bit - 1); i < num_buckets_; i += local_hight_bit) {
      dir_[i] = (i & local_hight_bit) == 0 ? bucket0 : bucket1;
    }
  }

  size_t bucket_index = indexOf(key);
  bucket = dir_[bucket_index];
  Node *node = bucket->insert(key, value);
  if(node == nullptr){
    return {end(), false};
  } else {
    return {Iterator(&dir_, bucket_index, node), true};
  }
}

 

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::begin() -> EXTENDIBLE_HASH_TABLE_TYPE::Iterator {
  return EXTENDIBLE_HASH_TABLE_TYPE::Iterator(&dir_, 0, dir_[0]->getList());
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::end() -> EXTENDIBLE_HASH_TABLE_TYPE::Iterator {
  return EXTENDIBLE_HASH_TABLE_TYPE::Iterator(&dir_, dir_.size(), nullptr);
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::cbegin() const -> EXTENDIBLE_HASH_TABLE_TYPE::ConstIterator{
  return static_cast<EXTENDIBLE_HASH_TABLE_TYPE::ConstIterator>(const_cast<EXTENDIBLE_HASH_TABLE_TYPE*>(this)->begin());
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::cend() const -> EXTENDIBLE_HASH_TABLE_TYPE::ConstIterator{
  return static_cast<EXTENDIBLE_HASH_TABLE_TYPE::ConstIterator>(const_cast<EXTENDIBLE_HASH_TABLE_TYPE*>(this)->end());
}

template <typename K, typename V>
void EXTENDIBLE_HASH_TABLE_TYPE::show() {
  std::cout << "Gloable depth = " << global_depth_ << std::endl;
  for (int i = 0; i < num_buckets_; i++) {
    std::shared_ptr<Bucket> bucket = dir_[i];
    std::bitset<4> bits(i);
    std::cout << bits << "(" << bucket->getDepth() << ")"
              << ":";
    for(Node *node = bucket->list_; node != nullptr; node = node->next){
      std::cout << node->value.first << ", ";
    }
    std::cout << std::endl;
  }
}

//===--------------------------------------------------------------------===//
// Bucket
//===--------------------------------------------------------------------===//
template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::Bucket::Bucket(size_t capcity, int depth) : capcity_(capcity), depth_(depth) {}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::Bucket::find(const K &key) -> Node * {
  for( Node *node = list_; node != nullptr; node = node->next){
    if(node->value.first == key ){
      return node;
    }
    
  }
  return nullptr;
}

// template <typename K, typename V>
// auto EXTENDIBLE_HASH_TABLE_TYPE::Bucket::remove(const K &key) -> bool {
//   for( Node *node = list_, *pre = nullptr; node != nullptr; node = node->next){
//     if(node->value.first == key ){
//       pre == nullptr ? list_ = nullptr : pre->next = node->next;
//       delete node;
//       size_--;
//       return true;
//     }
//     pre = node;
//   }
//   return false;
// }

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::Bucket::remove(const EXTENDIBLE_HASH_TABLE_TYPE::Node *node) -> bool {
  if(node->pre != nullptr){
    node->pre->next = node->next;
  } 

  if(node->next != nullptr){
    node->next->pre = node->pre;
  } 

  if(node == list_) {
    list_ = node->next;
  }
  

  delete node;
  size_--;
  return true;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::Bucket::insert(const K &key, const V &value) -> EXTENDIBLE_HASH_TABLE_TYPE::Node* {
  for( Node *node = list_; node != nullptr; node = node->next){
    if(node->value.first == key ){
      node->value.second = value;
      size_++;
      return node;
    }
  }
  if (!isFull()) {
    Node * node = new Node({key, value}, list_);
    if(list_ != nullptr){
      list_->pre = node;
    }
    
    list_ = node;
    size_++;
    return node;
  }

  return nullptr;
}


template class ExtendibleHashTable<int, std::string>;
template class ExtendibleHashTable<int, int>;

