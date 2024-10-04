#include "../Header/table.h"

template <typename K, typename V>
std::unique_ptr<bucket_t<K,V>> HashTable<K,V>::toBucket(K key, V val) {
  std::unique_ptr<bucket_t<K,V>> _new (new bucket_t<K, V>(key, val, HashTable::Hash(key)));
  return _new;
}


template <typename K, typename V>
void HashTable<K,V>::insert(K key, V val) {

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

