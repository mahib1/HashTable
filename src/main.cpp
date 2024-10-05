#include <iostream>
#include "../Header/table.h"

int main() {
  HashTable<int, std::string> myHash;

  myHash.insert(1, "hello"); 
  myHash.insert(4, "ayooo"); 
  myHash.insert(16, "whaaaaat");

  myHash.debug();


  std::vector<std::string> v1 = {"hehe" , "hoho" , "haha", "haha"};
  HashTable<std::size_t, std::string> myHash2(v1);

  myHash2.debug();

  std::cout << myHash.find(4) << std::endl;
  std::cout << *(myHash.get(4)) << std::endl;
  return 0;

}
