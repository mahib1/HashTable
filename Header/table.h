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

  //setters 
  void setSize(std::size_t _new); //done
  void setCap(std::size_t _new); //done

  std::size_t Hash(int key); //done
  std::size_t Hash(uint key);  //done
  std::size_t Hash(std::string &key); //done
  std::size_t Hash(char key); //done
  std::size_t Hash(bool key); //done
  std::size_t Hash(char* key); //done
  void freeTable(); //done
  
  template<typename U>
  std::size_t Hash(U* &key); //done
  std::size_t probe(std::size_t idx, K& key, int attempt); //done

  template <typename T>
  std::size_t secHash(const T& key); //done

  bucket_t<K,V>* toBucket(K &key, V &val); //done
  void resize(); //done
  bucket_t<K,V>* chainSearch(K &key, std::size_t idx); //done
  bucket_t<K,V>* fetch(K &key); //done

  //make a function here for resolving collisions 

public:
  HashTable(std::vector<V> &arr); //done
  HashTable(); //done

  template<typename C>
  HashTable(C cons, std::function<std::pair<K, V>(C)> *debug); //constructor for any data type
  ~HashTable(); //done

  void insert(K &key, V &val); //done 
  void erase(K &key, V &val); 
  bool find(K &key); //done
  V* get(K& key); //done
  void debug(); //done
};
