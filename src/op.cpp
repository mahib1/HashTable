#include "../Header/table.h"
#include <memory>

template <typename K, typename V>
void HashTable<K,V>::insert(K key, V val) {
  std::unique_ptr<bucket_t<K,V>> _new = HashTable::toBucket(key, val);
  std::size_t HashIdx = HashTable::Hash(key);

  if(_size == _capacity) {
    HashTable::resize(); 
  }

}

template <typename K, typename V>
std::unique_ptr<bucket_t<K,V>> HashTable<K,V>::toBucket(K key, V val) {
  std::unique_ptr<bucket_t<K,V>> _new (new bucket_t<K, V>(key, val, HashTable::Hash(key)));
  return _new;
}
