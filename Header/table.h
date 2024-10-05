#pragma once

#include <iostream>
#include <optional>
#include <vector>
#include <functional>
#include <string>

template<typename K, typename V>
struct bucket_t {
    K name;
    V value;
    std::size_t hashIdx;
    bucket_t<K, V>* next;

    bucket_t(K key, V val, std::size_t idx) : name(key), value(val), hashIdx(idx), next(nullptr) {}

    void add(bucket_t<K, V>* bucket_2) {
        next = bucket_2;
    }
};

template<typename K, typename V>
class HashTable {
private:
    std::size_t _size; 
    bucket_t<K, V>** _buff;
    std::size_t _capacity;

    void setSize(std::size_t _new);
    void setCap(std::size_t _new);
    
    std::size_t Hash(int key);
    std::size_t Hash(unsigned int key);
    std::size_t Hash(std::size_t key);
    std::size_t Hash(const std::string& key);
    std::size_t Hash(char key);
    std::size_t Hash(bool key);
    std::size_t Hash(char* key);
    void freeTable();
    
    template<typename U>
    std::size_t Hash(U*& key);
    
    std::size_t probe(std::size_t idx, const K& key, int attempt);
    bucket_t<K, V>* toBucket(const K& key, const V& val);
    void resize();
    bucket_t<K, V>* chainSearch(const K& key, std::size_t idx);
    bucket_t<K, V>* fetch(const K& key);

public:
    HashTable(std::vector<V>& arr);
    HashTable();
    ~HashTable();

    void insert(const K& key, const V& val);
    void erase(const K& key);
    bool find(const K& key);
    V* get(const K& key);
    void debug();
};

template <typename K, typename V>
void HashTable<K, V>::setSize(std::size_t _new) {
    _size = _new;
}

template <typename K, typename V>
void HashTable<K, V>::setCap(std::size_t _new) {
    _capacity = _new;
}

template <typename K, typename V>
HashTable<K, V>::HashTable() {
    _size = 0; 
    _capacity = 16; 
    _buff = new bucket_t<K, V>*[_capacity];

    for (std::size_t i = 0; i < _capacity; i++) {
        _buff[i] = nullptr;
    }
}

template <typename K, typename V>
HashTable<K, V>::HashTable(std::vector<V>& arr) {
    _size = 0; 
    _capacity = 16; 
    _buff = new bucket_t<K, V>*[_capacity];

    for (std::size_t i = 0; i < arr.size(); i++) {
        insert(i, arr[i]);
    }

    if (_size != arr.size()) perror("insert");
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    freeTable();
}

template <typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& val) {
    if (_size >= _capacity * 0.7) {
        resize();
    }

    std::size_t idx = Hash(key);
    bucket_t<K, V>* newBucket = toBucket(key, val);

    if (_buff[idx] == nullptr) {
        _buff[idx] = newBucket;
    } else {
        bucket_t<K, V>* temp = _buff[idx];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->add(newBucket);
    }
    _size++;
}

template <typename K, typename V>
void HashTable<K, V>::erase(const K& key) {
    std::size_t idx = Hash(key);
    bucket_t<K, V>* current = _buff[idx];
    bucket_t<K, V>* previous = nullptr;

    while (current != nullptr) {
        if (current->name == key) {
            if (previous == nullptr) {
                _buff[idx] = current->next; // Move the head of the list
            } else {
                previous->next = current->next;
            }

            delete current;

            _size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template <typename K, typename V>
void HashTable<K, V>::resize() {
    std::size_t _ocap = _capacity; 
    _capacity *= 2;

    bucket_t<K, V>** _newBuff = new bucket_t<K, V>*[_capacity];

    for (std::size_t i = 0; i < _capacity; i++) {
        _newBuff[i] = nullptr;
    }

    for (std::size_t i = 0; i < _ocap; i++) {
        bucket_t<K, V>* temp = _buff[i];
        while (temp != nullptr) {
            bucket_t<K, V>* next = temp->next; 
            std::size_t newIndex = Hash(temp->name); 
            temp->next = _newBuff[newIndex];
            _newBuff[newIndex] = temp;
            temp = next; 
        }
    }

    delete[] _buff; 
    _buff = _newBuff;
}

template <typename K, typename V>
void HashTable<K, V>::freeTable() {
    for (std::size_t i = 0; i < _capacity; i++) {
        if (_buff[i] == nullptr) continue; 

        bucket_t<K, V>* temp = _buff[i];
        while (temp != nullptr) {
            bucket_t<K, V>* toDel = temp; 
            temp = temp->next; 
            delete toDel;
        }
    }

    delete[] _buff;
}

template<typename K, typename V>
bucket_t<K, V>* HashTable<K, V>::toBucket(const K& key, const V& val) {
    return new bucket_t<K, V>(key, val, Hash(key));
}

template <typename K, typename V>
std::size_t HashTable<K, V>::Hash(int key) {
    return static_cast<std::size_t>(key) % _capacity;
}

template <typename K, typename V>
std::size_t HashTable<K, V>::Hash(unsigned int key) {
    return static_cast<std::size_t>(key) % _capacity;
}

template <typename K, typename V>
std::size_t HashTable<K, V>::Hash(std::size_t key) {
    return static_cast<std::size_t>(key) % _capacity;
}

template <typename K, typename V>
std::size_t HashTable<K, V>::Hash(const std::string& key) {
    std::size_t sum = 0; 

    for (char c : key) {
        sum += static_cast<int>(c); 
    }

    return sum % _capacity;
}

template <typename K, typename V>
std::size_t HashTable<K, V>::Hash(char key) {
    return static_cast<std::size_t>(key) % _capacity;
}

template <typename K, typename V>
std::size_t HashTable<K, V>::Hash(bool key) {
    return static_cast<std::size_t>(key) % _capacity;
}

template<typename K, typename V>
std::size_t HashTable<K, V>::Hash(char* key) {
    std::size_t sum = 0; 
    char* temp = key;
  
    while (*temp != '\0') {
        sum += static_cast<std::size_t>(*temp); 
        temp++;
    }

    return sum % _capacity;
}

template <typename K, typename V>
template <typename U>
std::size_t HashTable<K, V>::Hash(U*& key) {
    std::size_t address = reinterpret_cast<std::size_t>(key) % _capacity;
    address ^= (address >> 16);

    return address % _capacity;
}

template <typename K, typename V>
bool HashTable<K, V>::find(const K& key) {
    std::size_t idx = Hash(key);
    return fetch(key) != nullptr;
}

template <typename K, typename V>
V* HashTable<K, V>::get(const K& key) {
    bucket_t<K, V>* foundBucket = fetch(key);
    if (foundBucket) {
        return &foundBucket->value;
    }
    return nullptr;
}

template <typename K, typename V>
bucket_t<K, V>* HashTable<K, V>::fetch(const K& key) {
    std::size_t idx = Hash(key);
    return chainSearch(key, idx);
}

template <typename K, typename V>
bucket_t<K, V>* HashTable<K, V>::chainSearch(const K& key, std::size_t idx) {
    bucket_t<K, V>* temp = _buff[idx];
    while (temp != nullptr) {
        if (temp->name == key) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

template <typename K, typename V>
void HashTable<K, V>::debug() {
    for (int i = 0; i < _capacity; i++) {
        if (_buff[i] == nullptr) continue; 
        
        bucket_t<K, V>* temp = _buff[i]; 
        std::cout << "Index " << i << ": ";
        
        while (temp != nullptr) {
            std::cout << "(" << temp->name << ", " << temp->value << ") -> ";
            temp = temp->next; 
        }
        std::cout << "nullptr" << std::endl;
    }
}
