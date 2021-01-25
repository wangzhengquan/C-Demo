#include <iostream>
#include <string>
#include "brass.h"
using std::cin;
using std::cout;
using std::endl;

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
   test(1, 2);
   test(1);

}