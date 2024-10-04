#include "../Header/table.h"


template <typename K, typename V>
std::size_t HashTable<K,V>::Hash(int key) {
  return (std::size_t)key % _capacity;
}

template <typename K, typename V>
std::size_t HashTable<K,V>::Hash(std::string key) {
  std::size_t sum = 0; 

  for(int i = 0; i < key.length(); i++) {
    sum += (int)key[i]; 
  }

  return sum % _capacity;
}


template <typename K, typename V>
std::size_t HashTable<K,V>::Hash(bool key) {
  return key % _capacity;
}


template <typename K, typename V>
std::size_t HashTable<K,V>::Hash(uint key) {
  return (std::size_t)key % _capacity;
}

template <typename K, typename V>
std::size_t HashTable<K,V>::Hash(char key) {
  return (std::size_t)key % _capacity;
}


template<typename K, typename V>
std::size_t HashTable<K,V>::Hash(char* key) {
  std::size_t sum = 0; 
  char* temp = key;
  
  while(*temp != '\0') {
    sum += (std::size_t)(*temp); 
    temp++;
  }

  return sum % _capacity;
}

template <typename K, typename V>
template <typename U>
std::size_t HashTable<K,V>::Hash(U* key) {
  std::size_t address = reinterpret_cast<std::size_t>(key) % _capacity;
  address ^= (address >> 16);

  return address % _capacity;
}
