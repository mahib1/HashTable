#pragma once

#include "bucket.h"
#include <optional>
#include <sys/types.h>


template<typename K, typename V>
class HashTable {
private:
  std::size_t _size; 
  bucket_t<K,V>** _buff;
  std::size_t _capacity;

  std::size_t Hash(int &key); //done
  std::size_t Hash(uint &key);  //done
  std::size_t Hash(std::string &key); //done
  std::size_t Hash(char &key); //done
  std::size_t Hash(bool &key); //done
  std::size_t Hash(char* &key); //done
  
  template<typename U>
  std::size_t Hash(U* &key); //done
  std::size_t resolveHash(K &key, std::size_t _idx); // where probing and chaining comes in
  std::unique_ptr<bucket_t<K,V>> toBucket(K &key, V &val);
  void resize();
  bucket_t<K,V>* chainSearch(K &key, std::size_t idx); //done
  bucket_t<K,V>* changeIdxSearch(K &key, std::size_t idx);
  std::size_t probe(std::size_t idx);
  bucket_t<K,V>* fetch(K &key);
  //make a function here for resolving collisions 

public:
  HashTable(std::vector<V> &arr);
  HashTable(); //done

  template<typename C>
  HashTable(C cons, std::function<std::pair<K, V>(C)> *debug); //constructor for any data type
  ~HashTable(); 

  void insert(K &key, V &val); //doing 
  void erase(K &key, V &val); 
  bool find(K &key);
};
