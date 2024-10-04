// constructors and destructors

#include "../Header/table.h"
#include <cstddef>
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
HashTable<K,V>::HashTable(std::vector<V> &arr) {
  //initialize an empty hashTable;

  for(std::size_t i = 0 ; i < arr.size(); i++) {
    HashTable::insert(i, arr[i]);
  }

  if(_size != arr.size()) perror("insert");
}


template <typename K, typename V>
HashTable<K,V>* HashTable<K,V>::fetch(K key) {  
  
}


template <typename K, typename V>
void HashTable<K,V>::resize() {
  //Nisheeeeeeeeeeta here you go
  """This Function resizes the HashTable:""";
  """multiplies the capacity by 2 basically, while preserving the previous records of the table""";

}
