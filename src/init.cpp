// constructors and destructors

#include "../Header/table.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>

template <typename K, typename V>
HashTable<K,V>::HashTable() {
  //initialize an empty hashTable;
  _size = 0; 
  _capacity = 0; 
  _buff = std::nullptr_t();
}

template <typename K, typename V>
void HashTable<K,V>::resize() {

}


template <typename K, typename V>
HashTable<K,V>::HashTable(std::vector<V> &arr) {
  //initialize an empty hashTable;
  _size = arr.size(); 
  _capacity = arr.size(); 

  for(std::size_t i = 0 ; i < arr.size(); i++) {
    std::unique_ptr<bucket_t<std::size_t, V>> _new (new bucket_t<std::size_t, V>(i, arr[i], HashTable::Hash(i)));
  }
}

