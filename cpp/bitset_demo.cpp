#include "comm_inc.h"
#include <bitset> 
 
int main(int argc, char *argv[]) {
    uint64_t my_num = 6;
    std::bitset<64> bits (my_num);
    std::bitset<64> bits1(~my_num);
    std::bitset<64> bits2(!my_num);
    std::cout << bits << std::endl;
    std::cout << bits1 << std::endl;
    std::cout << bits2 << std::endl;

    int a = 7;
    std::bitset<8> bits3 (a);
    std::cout << bits3 << std::endl;

   
    return 0;
}
