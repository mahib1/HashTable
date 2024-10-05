#include "../Header/table.h"

template <typename K, typename V>
bucket_t<K,V>* HashTable<K,V>::toBucket(K &key, V &val) {
  bucket_t<K,V>* _new = new bucket_t<K, V>(key, val, HashTable::Hash(key));
  return _new;
}


template <typename K, typename V>
void HashTable<K,V>::insert(K &key, V &val) {

  bucket_t<K,V>* _new = HashTable::toBucket(key, val);

  if(_size >= _capacity/2) {
    HashTable::resize(); 
  }

  std::size_t _idx = HashTable::Hash(key);
  int attempt = 0;

  while(_buff[_idx] != nullptr && _buff[_idx] -> key != key) {
    attempt++;
    _idx = probe(_idx, key, attempt);
  }

  if(_buff[_idx] == nullptr) {
    _buff[_idx] = new bucket_t<K,V>(key, val, _idx); 
    _size++;
  } else {
    _buff[_idx] -> value = val;
  }

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


template <typename K, typename V>
bucket_t<K,V>* HashTable<K,V>::fetch(K &key) {  
  std::size_t _idx = HashTable::Hash(key); 
  int attempt = 0;
  
  while(_buff[_idx] != nullptr || chainSearch(key, _idx) != nullptr) {
    attempt ++;
    _idx = HashTable::probe(_idx, key, attempt);
  } 

  if(_buff[_idx] == nullptr) {
    return nullptr;
  } else {
    return chainSearch(key, _idx);
  }
}

template <typename K, typename V>
V* HashTable<K,V>::get(K& key) {
  bucket_t<K,V>* _res = HashTable::fetch(key);
  if(_res == nullptr) return nullptr; 

  return (_res -> value);
}

template <typename K, typename V>
bool HashTable<K,V>::find(K& key) {
  bucket_t _res = HashTable::fetch(key); 
  if(_res == nullptr) return false;

  return true;
}


template <typename K, typename V>
void HashTable<K,V>::debug() {
  for(int i = 0; i < _capacity ; i++) {
    if(_buff[i] == nullptr) continue; 
    
    bucket_t<K,V>* temp = _buff[i]; 
    while(temp != nullptr) { 
      std::cout << "key : " << temp -> key << ", value : " << temp -> val << std::endl;
      temp = temp -> next;
    }
  } 
}

