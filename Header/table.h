#pragma once

#include "bucket.h"
#include <optional>

template<typename K, typename V, typename C>
class HashTable {
private:
  std::size_t size; 
  bucket_t<K,V> *buff;

  std::size_t Hash(K Key);
  //make a function here for resolving collisions 

public:
  HashTable(std::vector<V> &arr);
  HashTable();
  HashTable(C cons, std::function<std::pair<K, V>(C)> *debug); //constructor for any data type
  ~HashTable(); 

  void insert(K key, V val); 
  void erase(K key, V val); 
  std::optional<V> find(K key);
};
