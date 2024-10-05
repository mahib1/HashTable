// constructors and destructors

#include "../Header/table.h"


template <typename K, typename V>
HashTable<K,V>::HashTable() {
  //initialize an empty hashTable;
  _size = 0; 
  _capacity = 16; 
  _buff = new bucket_t<K,V>*[_capacity];

  for(std::size_t i = 0 ; i < _capacity ; i++) {
    _buff[i] = nullptr;
  }

}

//setters
template <typename K, typename V>
void HashTable<K,V>::setSize(std::size_t _new) {
  _size = _new;
}


template <typename K, typename V>
void HashTable<K,V>::setCap(std::size_t _new) {
  _capacity = _new;
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
void HashTable<K,V>::resize() {
  std::size_t _ocap = _capacity; 
  _capacity *= 2;

  bucket_t<K,V>** _newBuff = new bucket_t<K,V>*[_capacity];

  for(int i = 0; i < _capacity ; i++) {
    _newBuff[i] = nullptr;
  }

  for(int i = 0; i < _ocap; i++) {
    _newBuff[i] = _buff[i];
  }

  freeTable(); 
  _buff = _newBuff;
}

template  <typename K, typename V>
void HashTable<K,V>::freeTable() {
  for(std::size_t i = 0; i < _capacity ; i++) {
    if(_buff[i] == nullptr) continue; 

    bucket_t<K,V>* temp = _buff[i];
    while(temp != nullptr) {
      bucket_t<K,V>* toDel = temp; 
      temp = temp -> next; 
      delete toDel;
    }
  }

  delete[] _buff;
}

template <typename K, typename V>
HashTable<K,V>::~HashTable() {
  freeTable();
}
