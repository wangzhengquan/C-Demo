#include "comm_inc.h"

class Example {
public:
  mutable int count = 0; // mutable member variable
  void increment() const { ++count; } // can modify count even though 'this' is const
};


class Example2 {
public:
  int count = 0; // mutable member variable
  void increment()  { ++count; } // can not modify count when 'this' is const
};


int main(int argc, char *argv[]) {
  const Example e;
  e.increment();
  std::cout << e.count << std::endl;


  Example2 e2;  //you cannot add "const" qualifier at the font of this line of code.
  e2.increment();
  
  // The following code will result in a compilation error.
  /**
   * 
    const Example2 e2;
    e2.increment();
  */
  return  0;
}
