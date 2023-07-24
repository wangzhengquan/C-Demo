#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
#include "log.h"

#define BUSTUB_ASSERT(expr, ...)        \
    if (!(expr)) { \
      ::fprintf(stdout, "assertion failed: %s \n", #expr); \
      ::fprintf(stdout, __VA_ARGS__);  \
      fflush(stdout); \
      while(true); \
   } 
  

void test(int n) {
  int a = static_cast<int>(ceil(static_cast<double>(n-1)/2));
  int b = static_cast<int>(ceil(static_cast<double>(n)/2)) - 1;
  if(a != b){
    printf("n=%d, a=%d, b=%d\n", n, a, b);
  }

}

 

class A{
public:
  int i_ {2};

  A(){}

  A(int i): i_(i){}

  ~A(){
    std::cout << "destroy " << i_ << std::endl;

  }

};
 

int main()
{
   // MY_ASSERT(1==2, "hello %s ", "world");
   // // BUSTUB_ASSERT(1==2, "hello %s ", "world");
   // MY_STATIC_ASSERT(1==1) ;
  // for(int n = 3; n<10; n++){
  //   test(n);
  // }
  //ref(nullptr);
  // A a1(1);
  // A a2(2);
  // A &a=a1;
  // auto *b=&a1;
   
  // a = a2;
  // cout << "a:" << a2.i_ << std::endl;
  // // for(int i=0 ;i <5; i++){
  // //   A a(i);
  // // }
  // 
  // std::string str = " hello " + 12 ;
  // cout << str << std::endl;
  // cout << "end" << std::endl;

  // A a1;
  // // A &a = nullptr;
  // a = a1;

  // std::ostringstream out;
  // out << "hello " ;
  // out << 1 ;

  // cout << out.str()<< std::endl;;
  // cout << "end" << std::endl;

}