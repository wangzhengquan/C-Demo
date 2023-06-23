/**
 * extendible_hash_table.h
 * 
 * Implementation of in-memory hash table using extendible hashing
 * 
 * 
 * https://www.geeksforgeeks.org/extendible-hashing-dynamic-approach-to-dbms/
 * https://en.wikipedia.org/wiki/Extendible_hashing
 */

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <memory>
#include <mutex>  // NOLINT
#include <shared_mutex>
#include <utility>
#include <vector>
#include <cassert>
#include <stdexcept>

#define DEFAULT_BUCKET_SIZE 4

#define EXTENDIBLE_HASH_TABLE_TEMPLATE_ARGUMENTS template <typename K, typename V>
#define EXTENDIBLE_HASH_TABLE_TYPE ExtendibleHashTable<K, V>

#define ASSERT(expr, message) assert((expr) && (message))

/**
 * ExtendibleHashTable implements a hash table using the extendible hashing algorithm.
 * @tparam K key type
 * @tparam V value type
 */
EXTENDIBLE_HASH_TABLE_TEMPLATE_ARGUMENTS
class ExtendibleHashTable  {
private:
  class Bucket;

public:
  template <bool>
  class ExtendibleHashTableIterator;

  template <bool>
  friend class ExtendibleHashTableIterator;

  using ElementType = std::pair<K, V>;
  using Iterator =  ExtendibleHashTableIterator<false>;
  using ConstIterator =  ExtendibleHashTableIterator<true>;
  /**
   * @brief Create a new ExtendibleHashTable.
   * @param bucket_size: fixed size for each bucket
   */
  explicit ExtendibleHashTable(size_t bucket_size = DEFAULT_BUCKET_SIZE);

  template <typename InputIt>
  ExtendibleHashTable(InputIt first, InputIt last, size_t bucket_size = DEFAULT_BUCKET_SIZE);

  ExtendibleHashTable(std::initializer_list<ElementType> init, size_t bucket_size = DEFAULT_BUCKET_SIZE);

  /**
   *
   * @brief Find the value associated with the given key.
   *
   * Use IndexOf(key) to find the directory index the key hashes to.
   *
   * @param key The key to be searched.
   * @param[out] value The value associated with the key.
   * @return True if the key is found, false otherwise.
   */
  auto find(const K &key) -> Iterator ;

  /**
   *
   * @brief Insert the given key-value pair into the hash table.
   * If a key already exists, the value should be updated.
   * If the bucket is full and can't be inserted, do the following steps before retrying:
   *    1. If the local depth of the bucket is equal to the global depth,
   *        increment the global depth and double the size of the directory.
   *    2. Increment the local depth of the bucket.
   *    3. Split the bucket and redistribute directory pointers & the kv pairs in the bucket.
   *
   * @param key The key to be inserted.
   * @param value The value to be inserted.
   */
  auto insert(const K &key, const V &value) -> std::pair<Iterator, bool>;

  /**
   * @brief Given the key, remove the corresponding key-value pair in the hash table.
   * Shrink & Combination is not required for this project
   * @param key The key to be deleted.
   * @return True if the key exists, false otherwise.
   */
  auto remove(const K &key) -> bool ;
  auto remove(Iterator pos) -> Iterator ;

  auto begin() -> Iterator;
  auto end() -> Iterator;

  auto cbegin() const -> ConstIterator;
  auto cend() const -> ConstIterator;

  void show();

private:
  /*****************************************************************
   * Must acquire latch_ first before calling the below functions. *
   *****************************************************************/

  /**
   * @brief For the given key, return the entry index in the directory where the key hashes to.
   * @param key The key to be hashed.
   * @return The entry index in the directory.
   */
  auto indexOf(const K &key) -> size_t;
  /**
   * @brief Get the global depth of the directory.
   * @return The global depth of the directory.
   */
  auto getGlobalDepth() const -> int;

  /**
   * @brief Get the local depth of the bucket that the given directory index points to.
   * @param dir_index The index in the directory.
   * @return The local depth of the bucket.
   */
  auto getLocalDepth(int dir_index) const -> int;

  /**
   * @brief Get the number of buckets in the directory.
   * @return The number of buckets in the directory.
   */
  auto getNumBuckets() const -> int;


private:
  struct Node {
    ElementType value;
    Node* next;
    Node* pre;
    Node(const ElementType& v = ElementType(), Node* n = nullptr, Node* p = nullptr) :
        value(v), next(n), pre(p) {}
  };
  /**
   * Bucket class for each hash table bucket that the directory points to.
   */
  class Bucket {
   public:
    friend class ExtendibleHashTable;
    explicit Bucket(size_t capcity, int depth = 0);

    /** @brief Check if a bucket is full. */
    inline auto isFull() const -> bool { return size_ >= capcity_; }

    /** @brief Get the local depth of the bucket. */
    inline auto getDepth() const -> int { return depth_; }

    /** @brief Increment the local depth of a bucket. */
    inline void incrementDepth() { depth_++; }

    inline auto getSize() const -> size_t { return size_; }
    inline auto getList() const -> Node * { return list_; }
    /**
     *
     * @brief Find the value associated with the given key in the bucket.
     * @param key The key to be searched.
     * @param[out] value The value associated with the key.
     * @return True if the key is found, false otherwise.
     */
    auto find(const K &key) -> Node *;

    /**
     * @brief Given the key, remove the corresponding key-value pair in the bucket.
     * @param key The key to be deleted.
     * @return True if the key exists, false otherwise.
     */
    // auto remove(const K &key) -> bool;
    auto remove(const Node *node) -> bool;

    /**
     * @brief Insert the given key-value pair into the bucket.
     *      1. If a key already exists, the value should be updated.
     *      2. If the bucket is full, do nothing and return false.
     * @param key The key to be inserted.
     * @param value The value to be inserted.
     * @return True if the key-value pair is inserted, false otherwise.
     */
    auto insert(const K &key, const V &value) -> Node *;

   private:
    const size_t capcity_;
    size_t size_ = 0;
    int depth_;
    Node *list_ = nullptr;
  };

public:
  template <bool IsConst = false>
  class ExtendibleHashTableIterator {

  public:
      /*
      * This alias is very important. When dealing with const_iterator, the value_type is always const, and
      * that prevents the client from modifying the elements via a const_iterator. The meta-function
      * std::conditional_t changes the value_type (at compile-time) to a const one if IsConst is true.
      */
      using value_type       =   std::conditional_t<IsConst, const ElementType, ElementType>;

      /*
      * Public aliases for this iterator class. Important so STL functions like std::iterator_traits
      * can parse this class for important information, like its iterator category.
      */
      using iterator_category =   std::forward_iterator_tag;
      using difference_type   =   std::ptrdiff_t;
      using pointer           =   value_type*;
      using reference         =   value_type&;

      /*
      * Friend declarations so the HashMap class this iterator is for can access the attributes of its iterators.
      * Also, to make conversions between iterator and const_iterator easy, we declare the corresponding
      * iterator and const_iterators as friends.
      */
      friend class ExtendibleHashTable;
      //friend class ExtendibleHashTableIterator<true>;
    // friend class ExtendibleHashTableIterator<false>;

      /*
      * Conversion operator: converts any iterator (iterator or const_iterator) to a const_iterator.
      *
      * Usage:
      *      iterator iter = map.begin();
      *      const_iterator c_iter = iter;    // implicit conversion
      *
      * Implicit conversion operators are usually frowned upon, because they can cause
      * some unexpected behavior. This is a rare case where a conversion operator is
      * very convenient. Many of the iterator functions in the HashMap class are
      * secretly using this conversion.
      *
      * Note: conversion in the opposite direction (const to non-const) is not safe
      * because that gives the client write access the map itself is const.
      */
      operator ExtendibleHashTableIterator<true>() const {
          return ExtendibleHashTableIterator<true>(dir_, bucket_index_, node_);
      }

      /*
      * Dereference operators: defines the behavior of dereferencing an iterator.
      *
      * Usage:
      *      auto [key, value] = *iter;
      *      auto value = iter->second;
      *      iter->second = 3; // if iter is a regular iterator (not a const_iterator)
      *
      * Note that dereferencing an invalid or end() iterator is undefined behavior.
      */
      reference operator*() const{
        return node_->value;
      }
      /*
      * operator-> is a bit of an odd-ball. When you write p->m, it is interpreted as (p.operator->())->m.
      * This means operator-> should return a pointer to the object that has the field m.
      *
      * For our usage, the client will write something like: iter->first, which is interpreted
      * as (iter.operator->())->first. This means operator-> should return a pointer to the
      * object that has the 'first' and 'second' field, i.e. a pointer to the std::pair/the value of that node.
      */
      pointer operator->() const{
        return &(node_->value); 
      }

      /*
      * Increment operators: moves the iterator to point to the next element, or end().
      *
      * Usage:
      *      ++iter;         // prefix
      *      iter++;         // postfix
      *
      * Note: the prefix operator first increments, and the returns a reference to itself (which is incremented).
      * The postfix operator returns a copy of the original iterator, while the iterator itself is incremented.
      *
      * Note that incrementing an invalid or end() iterator is undefined behavior.
      */
      ExtendibleHashTableIterator& operator++(){
          node_ = node_->next; 
          if (node_ == nullptr) { // if you reach the end of the bucket, find the next bucket
              for (++bucket_index_; bucket_index_ < dir_->size(); ++bucket_index_) {
                  node_ = (*dir_)[bucket_index_]->getList();
                  if (node_ != nullptr) {
                      return *this;
                  }
              }
          }
          return *this;
      }

      ExtendibleHashTableIterator operator++(int){
        auto tmp = *this; // calls the copy constructor to create copy
        ++(*this);
        return tmp;
      }

      /*
      * Equality operator: decides if two iterators are pointing to the same element.
      *
      * Usage:
      *      if (iter == map.end()) {...};
      */
      friend bool operator==(const ExtendibleHashTableIterator& lhs, const ExtendibleHashTableIterator& rhs){
        return lhs.bucket_index_ == rhs.bucket_index_ && lhs.node_ == rhs.node_;
      }

      /*
      * Inequality operator: decides if two iterators are pointing to different elements.
      *
      * Usage:
      *      if (iter != map.end()) {...};
      */
      friend bool operator!=(const ExtendibleHashTableIterator& lhs, const ExtendibleHashTableIterator& rhs){
        return !(lhs == rhs);
      }

      /*
      * Special member functions: we explicitly state that we want the default compiler-generated functions.
      * Here we are following the rule of zero. You should think about why that is correct.
      */
      ExtendibleHashTableIterator(const ExtendibleHashTableIterator& rhs) = default;
      ExtendibleHashTableIterator& operator=(const ExtendibleHashTableIterator& rhs) = default;

      ExtendibleHashTableIterator(ExtendibleHashTableIterator&& rhs) = default;
      ExtendibleHashTableIterator& operator=(ExtendibleHashTableIterator&& rhs) = default;


  private:
      /*
      * Instance variable: a pointer to the _buckets_array of the HashMap this iterator is for.
      */
      std::vector<std::shared_ptr<Bucket> > * dir_;
      
      /*
      * Instance variable: the index of the bucket that bucket is in.
      */
      size_t bucket_index_;
      Node * node_;

      /*
      * Private constructor for a ExtendibleHashTableIterator.
      * Friend classes can access the private members of class it is friends with, 
      * so HashMap is able to call ExtendibleHashTableIterator's private constructor 
      * (e.g, in begin()). We want the ExtendibleHashTableIterator constructor to be private 
      * so a client can't randomly construct a ExtendibleHashTableIterator without asking for one 
      * through the HashMap's interface.
      */
      ExtendibleHashTableIterator(std::vector<std::shared_ptr<Bucket> > * dir, size_t bucket_index, Node * node) : dir_(dir),
      bucket_index_(bucket_index),
      node_(node) { }

       

  };
  

  

private:

  int global_depth_;    // The global depth of the directory
  size_t bucket_size_;  // The size of a bucket
  int num_buckets_;     // The number of buckets in the hash table
  mutable std::shared_mutex mutex_;
  std::vector<std::shared_ptr<Bucket>> dir_;  // The directory of the hash table

};

