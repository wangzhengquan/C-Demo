#include <iostream>
#include <string>
#include <memory>
#include "extendible_hash_table.h"
using std::cin;
using std::cout;
using std::endl;
 

void test()
{
  // auto table = std::make_unique<ExtendibleHashTable<int, int>>(4);
  ExtendibleHashTable<int, int> table(4);
  std::cout << "====Mytest" << std::endl;
  ASSERT(table.empty() , "assert empty");
  table.insert(16, 16);
  table.insert(4, 4);
  table.insert(6, 6);
  table.insert(22, 22);
  table.insert(24, 24);
  table.insert(10, 10);
  table.insert(31, 31);
  table.insert(7, 7);
  table.insert(9, 9);
  table.insert(20, 20);
  table.insert(26, 26);
  table.insert({8, 8});


  std::cout << "----print table ---- " << std::endl;
  table.show();


  std::cout << "----copy constructor ---- " << std::endl;
  ExtendibleHashTable<int, int> table2 = table;
  table2.show();

  std::cout << "----move constructor ---- " << std::endl;
  ExtendibleHashTable<int, int> table3 = std::move(table2);
  table3.show();



  std::cout << "----iterator first ---- " << std::endl;
  ExtendibleHashTable<int, int>::Iterator it = table.begin();
  ExtendibleHashTable<int, int>::ConstIterator cit = it;
  std::cout << cit->first << "\n ";
 
 
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

  std::cout << "----remove---- " << std::endl;
  auto it2 = table.find(10);
  std::cout << "find " << it2->first << std::endl;
  table.erase(it2);
  ASSERT(table.find(10) == table.end(), "remove failed");

  table.erase(31);
  ASSERT(table.find(31) == table.end(), "remove failed");
  table.show();
}

void test_remove() {
	std::cout << "----test_remove---- " << std::endl;
   ExtendibleHashTable<int, std::string> c =
    {
        {1, "one" }, {2, "two" }, {3, "three"},
        {4, "four"}, {5, "five"}, {6, "six"  }
    };

    for (auto& p : c)
        std::cout << p.second << ", ";

    std::cout << std::endl;
 
    // erase all odd numbers from c
    for (auto it = c.begin(); it != c.end();)
    {
        if (it->first % 2 != 0)
            it = c.erase(it);
        else
            ++it;
    }

    std::cout << std::endl;
 
    for (auto& p : c)
        std::cout << p.second << ", ";

    std::cout << std::endl;
}

int main(){
  test();
  
  test_remove();
}