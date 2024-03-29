
template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(size_t bucket_size, int global_depth)
    : bucket_size_(bucket_size), 
      global_depth_(global_depth),  
      num_buckets_(1 << global_depth),
      dir_(num_buckets_) {

  for (int i = 0; i < num_buckets_; i++) {
    dir_[i] = std::make_shared<Bucket>(bucket_size_, global_depth_);
  }
}

template <typename K, typename V>
template <typename InputIt>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(InputIt first, InputIt last, size_t bucket_size) :
   ExtendibleHashTable(bucket_size) {
   for (auto iter = first; iter != last; ++iter) {
      insert(*iter);
   }
}

template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(std::initializer_list<ElementType> init, size_t bucket_size) :
   ExtendibleHashTable{init.begin(), init.end(), bucket_size} {
}

// copy constructor
template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(const ExtendibleHashTable& other) :
ExtendibleHashTable(other.bucket_size_, other.global_depth_) {
  for(auto &pair : other){
    insert(pair);
  }
}

// move constructor
template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTable(ExtendibleHashTable&& other) : 
bucket_size_(other.bucket_size_), global_depth_(other.global_depth_),  num_buckets_(1 << other.global_depth_) {
  dir_.resize(num_buckets_);
  for (int i = 0; i < num_buckets_; i++) {
    dir_[i] = other.dir_[i];  
  }
  other.clear();
}

// copy assignment operator
template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE& EXTENDIBLE_HASH_TABLE_TYPE::operator=(const ExtendibleHashTable& other){
  if (this == &other)
    return *this;
  clear();
  for(auto &pair : other){
    insert(pair);
  }
  return *this;
}

// move assignment operator
template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE& EXTENDIBLE_HASH_TABLE_TYPE::operator=(ExtendibleHashTable&& other) {
  if (this == &other)
    return *this;
  bucket_size_ = other.bucket_size_;
  global_depth_= other.global_depth_;
  num_buckets_ = other.num_buckets_;
  dir_.resize(num_buckets_);
  for (int i = 0; i < num_buckets_; i++) {
    dir_[i] = other.dir_[i];  
  }
  other.clear();
  return *this;
}
 

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::indexOf(const K &key) -> size_t {
  int mask = (1 << global_depth_) - 1;
  return std::hash<K>()(key) & mask;
}



template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::find(const K &key) const -> ConstIterator {
  return static_cast<ConstIterator>(const_cast<EXTENDIBLE_HASH_TABLE_TYPE*>(this)->find(key));
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::find(const K &key) -> Iterator {
  size_t bucket_index = indexOf(key);
  Node *node = dir_[bucket_index]->find(key);

  if(node == nullptr){
    return end();
  }

  return Iterator(&dir_, bucket_index, node);
  
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::erase(const K &key) -> bool {
  Iterator pos = find(key);
  if(pos == end()){
    return false;
  }
  erase(pos);
  return true;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::erase(EXTENDIBLE_HASH_TABLE_TYPE::Iterator pos) -> Iterator {
  std::shared_ptr<Bucket> bucket = dir_[pos.bucket_index_];
  bucket->remove(pos++.node_);
  size_--;
  return pos;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::insert(const ElementType & pair) -> std::pair<Iterator, bool> {
  return insert(pair.first, pair.second);
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::insert(const K &key, const V &value) -> std::pair<Iterator, bool> {
  Iterator pos = find(key);
  if(pos != end()){
    return {pos, false};
  }
  return insert_or_assign(key, value);
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::insert_or_assign(const ElementType & pair) -> std::pair<Iterator, bool> {
  return insert_or_assign(pair.first, pair.second);
}


template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::insert_or_assign(const K &key, const V &value) -> std::pair<Iterator, bool> {
  // std::cout << "insert(" << key <<"," << value << ")"<< std::endl;
  size_t bucket_index = indexOf(key);
  std::shared_ptr<Bucket> bucket = dir_[bucket_index];
  while (bucket->isFull()) {
    // extend dir
    if (bucket->getDepth() == global_depth_) {
      dir_.resize(num_buckets_*2);
      for (int i = 0; i < num_buckets_; i++) {
        dir_[i + num_buckets_] = dir_[i];
      }
      num_buckets_ *= 2;
      global_depth_++;
    }

    // split bucket
    std::shared_ptr<Bucket> bucket0 = std::make_shared<Bucket>(bucket_size_, bucket->getDepth() + 1);
    std::shared_ptr<Bucket> bucket1 = std::make_shared<Bucket>(bucket_size_, bucket->getDepth() + 1);
    int local_hight_bit = 1 << (bucket->getDepth());
    // split the bucket into two bucket according to the (bucket->getDepth()+1)'th bit of the hash value of the node's key 
    for(Node *node = bucket->list_; node != nullptr; node = node->next){
      std::shared_ptr<Bucket> new_buket = (std::hash<K>()(node->value.first) & local_hight_bit) == 0 ? bucket0 : bucket1;
      new_buket->insert_or_assign(node->value.first, node->value.second);
    }

    /* 
     * All of the dir items whose index  has the same low 'bucket->getDepth()' bits with 'bucket_index' points to the same bucket,
     * All of them should be split into two buckets base on the (bucket->getDepth()+1)'th bit of their corresponding index.
     */
    // int i = std::hash<K>()(key) & (local_hight_bit - 1)
    for (int i = std::hash<K>()(key) & (local_hight_bit - 1); i < num_buckets_; i += local_hight_bit) {
      // if bucket->getDepth()'th bit of the i is 0 set dir_[i] points to bucket0, else to bucket1;
      dir_[i] = (i & local_hight_bit) == 0 ? bucket0 : bucket1;
    }

    bucket_index = indexOf(key);
    bucket = dir_[bucket_index];
  }

  
  auto [node, is_insert] = bucket->insert_or_assign(key, value);
  if(node == nullptr){
    return {end(), false};
  } else {
    if(is_insert)
      size_++;
    return {Iterator(&dir_, bucket_index, node), is_insert};
  }
}

template <typename K, typename V>
inline auto EXTENDIBLE_HASH_TABLE_TYPE::empty() const -> bool {
  // return size_ == 0;
  return cbegin() == cend();
}

template <typename K, typename V>
void EXTENDIBLE_HASH_TABLE_TYPE::clear() {
  // for (int i = 0; i < num_buckets_; i++) {
  //   // delete old Bucket
  //   dir_[i] = nullptr;
  // }
  global_depth_ = 0;
  num_buckets_ = (1 << global_depth_);
  dir_.resize(num_buckets_);
  for (int i = 0; i < num_buckets_; i++) {
    dir_[i] = std::make_shared<Bucket>(bucket_size_, global_depth_);
  }
  size_=0;
  
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::at(const K& key) -> V&{
  Iterator it = find(key);
  if(it == end()){
     throw std::out_of_range("at: key not found");
  }
  return it->second;
     
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::at(const K& key) const -> const V& {
  ConstIterator it = find(key);
  if(it == cend()){
     throw std::out_of_range("at: key not found");
  }
  return it->second;
}


template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::begin() -> Iterator {
  return EXTENDIBLE_HASH_TABLE_TYPE::Iterator(&dir_, 0, dir_[0]->getList());
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::end() -> Iterator {
  return EXTENDIBLE_HASH_TABLE_TYPE::Iterator(&dir_, dir_.size(), nullptr);
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::begin() const -> ConstIterator{
  return cbegin();
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::end() const -> ConstIterator{
  return cend();
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::cbegin() const -> ConstIterator{
  return static_cast<EXTENDIBLE_HASH_TABLE_TYPE::ConstIterator>(const_cast<EXTENDIBLE_HASH_TABLE_TYPE*>(this)->begin());
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::cend() const -> ConstIterator{
  return static_cast<EXTENDIBLE_HASH_TABLE_TYPE::ConstIterator>(const_cast<EXTENDIBLE_HASH_TABLE_TYPE*>(this)->end());
}


template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::operator[](const K& key) -> V& {
   return insert({key, {}}).first->second;
}

template <typename K, typename V>
void EXTENDIBLE_HASH_TABLE_TYPE::show() {
  std::cout << "---------- Table Structure -----------" << std::endl;
  std::cout << "Gloable depth = " << global_depth_ << std::endl;
  for (int i = 0; i < num_buckets_; i++) {
    std::shared_ptr<Bucket> bucket = dir_[i];
    std::bitset<32> bits(i);
    std::cout << bits << "(depth=" << bucket->getDepth() << ")" << " : ";
              
    for(Node *node = bucket->list_; node != nullptr; node = node->next){
      std::cout << "(" << node->value.first << ", " << node->value.second << ") ";
    }
    std::cout << std::endl;
  }
  std::cout << "--------------------------------------" << std::endl;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::check() -> bool{
  int suc = true;
  for (int i = 0; i < num_buckets_; i++) {
    std::shared_ptr<Bucket> bucket = dir_[i];
    if(!bucket){
      std::cout << "bucket " << i <<" is null. ";
      suc = false;
      continue;
    }
    int mask = (1 << (bucket->getDepth())) - 1;   
    for(Node *node = bucket->list_; node != nullptr; node = node->next){
      int keybit = std::hash<K>()(node->value.first ) & mask;
      if(keybit != (i & mask)){
        suc = false;
        std::cout << "keybit , i=" << i << ", key=" << node->value.first << std::endl;
      }
    }
  }
  return suc;
}


//===--------------------------------------------------------------------===//
// Bucket
//===--------------------------------------------------------------------===//
template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::Bucket::Bucket(size_t capcity, int depth) : capcity_(capcity), depth_(depth) {
  std::cout << "Bucket construct" << std::endl;
}

template <typename K, typename V>
EXTENDIBLE_HASH_TABLE_TYPE::Bucket::~Bucket(){
  // std::cout << "~Bucket" << std::endl;
  clear();
}

template <typename K, typename V>
void EXTENDIBLE_HASH_TABLE_TYPE::Bucket::clear(){
  Node *node = list_;
  while (node != nullptr) {
    auto temp = node;
    node = node->next;
    delete temp;
    // temp = nullptr;
  }
  list_ = nullptr;
  size_ = 0;
  depth_ = 0;
}

template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::Bucket::find(const K &key) -> Node * {
  for( Node *node = list_; node != nullptr; node = node->next){
    if(node->value.first == key ){
      return node;
    }
    
  }
  return nullptr;
}


template <typename K, typename V>
auto EXTENDIBLE_HASH_TABLE_TYPE::Bucket::remove(const Node *node) -> bool {
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
auto EXTENDIBLE_HASH_TABLE_TYPE::Bucket::insert_or_assign(const K &key, const V &value) -> std::pair<Node*, bool> {
  for( Node *node = list_; node != nullptr; node = node->next){
    if(node->value.first == key ){
      node->value.second = value;
      return {node, false};
    }
  }
  if (!isFull()) {
    Node * node = new Node({key, value}, list_);
    if(list_ != nullptr){
      list_->pre = node;
    }
    
    list_ = node;
    size_++;
    return {node, true};
  }

  return {nullptr, false};
}




//===--------------------------------------------------------------------===//
// ExtendibleHashTableIterator
//===--------------------------------------------------------------------===//
template <typename K, typename V>
template <bool IsConst>
EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTableIterator<IsConst>& EXTENDIBLE_HASH_TABLE_TYPE::ExtendibleHashTableIterator<IsConst>::operator++(){
  node_ = node_->next; 
  if (node_ == nullptr) { // if you reach the end of the bucket, find the next bucket
      for (++bucket_index_; bucket_index_ < dir_->size(); ++bucket_index_) {
          std::shared_ptr<Bucket> bucket = (*dir_)[bucket_index_];
          size_t local_hight_bit = 1 << (bucket->getDepth());
          if(bucket_index_ < local_hight_bit) {
            node_ = bucket->getList();
            if (node_ != nullptr) {
                return *this;
            }
          }
      }
  }
  return *this;
}


// template class ExtendibleHashTable<int, std::string>;
// template class ExtendibleHashTable<int, int>;
// template class ExtendibleHashTable<std::string, int>;



