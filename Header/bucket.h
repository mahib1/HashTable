#pragma once

/*
 * This is the Bucket type definition 
*/

#include <iostream>

template<typename K, typename V>
struct bucket_t {
  K name;
  V value;
  std::size_t hashIdx;
  bucket_t<K,V>* next;
  
  bucket_t(K key, V val, std::size_t idx) : name(key), value(val), hashIdx(idx), next(nullptr) {};
  void add(bucket_t &bucket_2) {
    this.next = bucket_2;
  };
};

