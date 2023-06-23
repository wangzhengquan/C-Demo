#include "comm_inc.h"
#include <bitset> 
 
int main(int argc, char *argv[]) {
    // uint64_t my_num = 6;
    // std::bitset<64> bits (my_num);
    // std::bitset<64> bits1(~my_num);
    // std::bitset<64> bits2(!my_num);
    // std::cout << bits << std::endl;
    // std::cout << bits1 << std::endl;
    // std::cout << bits2 << std::endl;

    int i = -1;
    // uint b = static_cast<uint>(i);
    uint b = uint(i);
    std::cout << b << std::endl;
    return 0;
}
