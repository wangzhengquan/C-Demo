#include "comm_inc.h"
#include <bitset> 
 
// int main(int argc, char *argv[]) {
     
// }

// primary template
template<class T>
struct A
{ 
    struct B {};
 
    void f(){
        printf("hello");
    }
 
    struct D { void g(); };
 
    T h();
 
    template<T U>
    T i();
};
 
// full specialization
template<>
struct A<int>
{
    struct B {};
 
    int f();
 
    struct D { void g(); };
 
    template<int U>
    int i();
};


// another full specialization
template<>
struct A<float*>
{
    int *h();
};
 
int main()
{
    // float f = 1.0;
    A<char> a;
    a.f();
    
}
