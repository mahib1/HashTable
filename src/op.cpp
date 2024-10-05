#include "../Header/table.h"

template <typename K, typename V>
std::unique_ptr<bucket_t<K,V>> HashTable<K,V>::toBucket(K &key, V &val) {
  std::unique_ptr<bucket_t<K,V>> _new (new bucket_t<K, V>(key, val, HashTable::Hash(key)));
  return _new;
}


template <typename K, typename V>
void HashTable<K,V>::insert(K &key, V &val) {

  std::unique_ptr<bucket_t<K,V>> _new = HashTable::toBucket(key, val);

  if(_size >= _capacity) {
    HashTable::resize(); 
  }

  std::size_t _idx = HashTable::Hash(key);

  if(_buff[_idx] != nullptr) {
    HashTable::resolveHash(key, _idx);
  }
  

  _buff[_idx] = _new;
  _size++;
}

template <typename K, typename V>
bucket_t<K,V>* HashTable<K,V>::chainSearch(K &key, std::size_t idx) {
  if(_buff[idx] == nullptr) {
    return nullptr;
  }

  if(_buff[idx] -> key == key) {
    return _buff[idx];
  }

  bucket_t<K,V>* temp = _buff[idx]; 

  while(temp != nullptr) {
    if (temp -> key == key) {
      return temp;
    }

    temp = temp -> next;
  }

  return nullptr;

}

//this function may/may not work as of now
template <typename K, typename V>
bucket_t<K,V>* HashTable<K,V>::changeIdxSearch(K &key, std::size_t idx) {
  std::size_t _newIdx = HashTable::probe(idx);

  if(_buff[_newIdx] == nullptr) {
    return nullptr; 
  }

  while(_buff[_newIdx] != nullptr) {
    bucket_t<K,V>* temp = chainSearch(key, _newIdx); 
    if(temp != nullptr) return temp;

    _newIdx = HashTable::probe(_newIdx);
  }

  return nullptr;
}

template <typename K, typename V>
bucket_t<K,V>* HashTable<K,V>::fetch(K &key) {  
  std::size_t idx = HashTable::Hash(key); 
  bucket_t<K,V>* result = HashTable::chainSearch(key, idx);
  if(result == nullptr) {
    bucket_t<K,V>* temp = HashTable::changeIdxSearch(key, idx);
    if(temp == nullptr) return nullptr;

    return temp;
  }

  return nullptr;
}


