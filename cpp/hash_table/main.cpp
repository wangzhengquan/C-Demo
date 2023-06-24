#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
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
  table.clear();
}

void test_at() {
	std::cout << "----test2---- " << std::endl;
	ExtendibleHashTable<int, std::string> map =
	 {
	     {1, "one" }, {2, "two" }, {3, "three"},
	     {4, "four"}, {5, "five"}, {6, "six"  }
	 };
   map.show();

  try
  {
  	std::cout << "map.at(1) =  " <<  map.at(1) << std::endl;
   map.at(1) = "hello one";
   std::cout << "map.at(1) =  " <<  map.at(1) << std::endl;
   // map.show();
  }
  catch (const std::exception& e)
  {
    cout << e.what() << '\n';
  }

  try
  {
  	// std::cout << " map.at(10) =  " <<  map.at(10) << std::endl;
   map.at(10) = "world";
   // std::cout << " map.at(10) =  " <<  map.at(10) << std::endl;
   // map.show();
   std::cout << "  after  exception " << std::endl;
  }
  catch (const std::exception& e)
  {
    cout << e.what() << '\n';
  }

  std::cout << "map[6] =  " <<  map[6] << std::endl;
  map[7] = "seven";
  std::cout << "map[7] =  " <<  map[7] << std::endl;
  
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

 
void test_move_assiment() {
	 std::cout << "----test_move---- " << std::endl;
    ExtendibleHashTable<std::string, int> map1 {{"A", 1}, {"B", 2}};
    ExtendibleHashTable<std::string, int> map2 {{"C", 3}};

    std::unordered_map<std::string, int> answer1 {{"A", 1}, {"B", 2}};
    std::unordered_map<std::string, int> answer2 {{"C", 3}};

    map1 = std::move(map2) = std::move(map2) = std::move(map1);
    // map1 = std::move(map2) =  std::move(map1);
    for (auto& p : map1){
        std::cout << "(" << p.first << "," << p.second << ") ";
    }
     std::cout << std::endl;

    answer1 = std::move(answer2) = std::move(answer2) = std::move(answer1);
    for (auto& p : answer1){
        std::cout << "(" << p.first << "," << p.second << ") ";
    }
    std::cout << std::endl;
}

int main(){
  test();
  
  test_remove();
  test_at();
  test_move_assiment();
	ExtendibleHashTable<int, std::string> c =
    {
        {1, "one" }, {2, "two" }, {3, "three"},
        {4, "four"}, {5, "five"}, {6, "six"  }
    };
    c.show();

    
   std::cout << std::endl;
}