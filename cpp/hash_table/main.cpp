#include <iostream>
#include <string>
#include <memory>
#include "extendible_hash_table.h"
using std::cin;
using std::cout;
using std::endl;
 

int main()
{
  // auto table = std::make_unique<ExtendibleHashTable<int, int>>(4);
  ExtendibleHashTable<int, int> table(4);
  std::cout << "====Mytest" << std::endl;
  table.Insert(16, 16);
  table.Insert(4, 4);
  table.Insert(6, 6);
  table.Insert(22, 22);
  table.Insert(24, 24);
  table.Insert(10, 10);
  table.Insert(31, 31);
  table.Insert(7, 7);
  table.Insert(9, 9);
  table.Insert(20, 20);
  table.Insert(26, 26);

  table.Show();
 
 
  std::cout << "----iterator---- " << std::endl;
  for(auto & [key, val] : table){
    std::cout << key << ", ";
  }
  std::cout << std::endl;
  for (auto  it = table.begin(); it != table.end(); ++it) {
    std::cout << it->first << ", ";
  }
  std::cout << std::endl;
   std::cout << "----const iterator---- " << std::endl;
  for (auto  it = table.cbegin(); it != table.cend(); ++it) {
    std::cout << it->first << ", ";
  }
  std::cout << std::endl;

  int result;
  table.Find(31, result);
  std::cout << "find " << result << std::endl;
}