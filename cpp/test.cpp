#include <iostream>
#include <string>
#include "brass.h"
using std::cin;
using std::cout;
using std::endl;

#define BUSTUB_ASSERT(expr, ...)		\
	if (!(expr)) { \
      fprintf(stdout, "assertion failed: %s", #expr); \
   	::fprintf(stdout, __VA_ARGS__);  \
      while(true); \
   } \
  

const int CLIENTS = 4;
int test(int a, int b) {
	cout << "a, b" << endl;
	return 1;
}

int test(int a) {
	cout << "a" << endl;
	return 1;
}

int main()
{
   BUSTUB_ASSERT(1==2, "hello %s", "world");

}