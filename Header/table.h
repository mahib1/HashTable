#pragma once

#include "bucket.h"
#include <optional>
#include <sys/types.h>

template<typename K, typename V>
class HashTable {
private:
  std::size_t _size; 
  bucket_t<K,V> *_buff;
  std::size_t _capacity;

  std::size_t Hash(int key); //done
  std::size_t Hash(uint key);  //done
  std::size_t Hash(std::string key); //done
  std::size_t Hash(char key); //done
  std::size_t Hash(bool key); //done
  std::size_t Hash(char* key); //done
  
  template<typename U>
  std::size_t Hash(U* Key); //done
  std::size_t resolveHash(); // where probing and chaining comes in
  //make a function here for resolving collisions 

public:
  HashTable(std::vector<V> &arr);
  HashTable();

  template<typename C>
  HashTable(C cons, std::function<std::pair<K, V>(C)> *debug); //constructor for any data type
  ~HashTable(); 

  void insert(K key, V val); 
  void erase(K key, V val); 
  std::optional<V> fetch(K key);
  bool find(K key);
};
