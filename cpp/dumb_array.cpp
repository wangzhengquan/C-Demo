/**
 * https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
 * https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <memory>
#include <mutex>  // NOLINT
#include <shared_mutex>
#include <utility>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <bitset>
#include <cstdlib>
#include <functional>

#include <algorithm> // std::copy
#include <cstddef> // std::size_t

class DumbArray
{
public:
    // (default) constructor
    DumbArray(std::size_t size = 0)
        : size_(size),
          array_(size ? new int[size]() : nullptr)
    {
    }

    //  copy constructor
    DumbArray(const DumbArray& other)
        : size_(other.size_),
          array_(size_ ? new int[size_] : nullptr)
    {
        std::cout << " copy constructor called.\n";
        // note that this is non-throwing, because of the data
        // types being used; more attention to detail with regards
        // to exceptions must be given in a more general case, however
        std::copy(other.array_, other.array_ + size_, array_);
    }

    //  move constructor
    DumbArray(DumbArray&& other) noexcept 
        : DumbArray() // initialize via default constructor, C++11 only
    {
        std::cout << " move constructor called.\n";
        swap(*this, other);
    }

    /*
    // method 1: move constructor
    DumbArray(DumbArray && other): size_(other.size_) ,
        array_ = other.array_      // steal address
    {
        
        other.array_ = nullptr;    // give old object nothing in return
        other.size_ = 0;
    }
    */

    
    // copy assignment operator
    DumbArray& operator=(const DumbArray& other) 
    {
        std::cout << " copy assignment operator called.\n";
        DumbArray temp(other);
        swap(const_cast<DumbArray&>(*this), temp); // (2)

        return *this;
    }

    // method 1: copy assignment operator 
    /*
    DumbArray& operator=(const DumbArray& other)
    {
        if (this != &other) // (1)
        {
            // get rid of the old data...
            delete [] array_;  
            array_ = nullptr;  

            // ...and put in the new
            size_ = other.size_; 
            array_ = size_ ? new int[size_] : nullptr;  
            std::copy(other.array_, other.array_ + size_, array_);  
        }

        return *this;
    }
    */

    // method 2: copy assignment operator 
    /*
    DumbArray& operator=(const DumbArray& other)
    {
     if (this != &other) 
     {
         // get the new data ready before we replace the old
         std::size_t newSize = other.size_;
         int* newArray = newSize ? new int[newSize]() : nullptr; 

         // If the above statement throws,
         // the object is still in the same state as before.
         // None of the following statements will throw an exception :)
         std::copy(other.array_, other.array_ + newSize, newArray); 

         // replace the old data (all are non-throwing)
         delete [] array_;
         size_ = newSize;
         array_ = newArray;
     }

     return *this;
    }
    */
    
    // move Assignment operator
    DumbArray& operator=(DumbArray && other) noexcept
    {
        std::cout << " move assignment operator called.\n";
        swap(*this, other);
        delete other.array_;
        other.array_ = nullptr;
        other.size_ = 0;
        return *this; 

    }


    // method 1: move assignment operator 
    /*
    DumbArray & operator=(DumbArray && other) 
    {
        std::cout << "move assignment operator called:\n";
        if (this == &other)
            return *this;
        delete [] array_;
        array_ = other.array_;
        size_ = other.size_;
        other.size_ = 0;
        other.array_ = nullptr;
        return *this;
    }
    */

    // destructor
    ~DumbArray()
    {
        delete [] array_;
    }

     void swap(DumbArray& first, DumbArray& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.size_, second.size_);
        swap(first.array_, second.array_);
    }

    int& operator[](int i) {
        return array_[i];
    }
    const int& operator[](int i) const{
        return array_[i];
    }

    friend std::ostream& operator<<(std::ostream& os, const DumbArray& obj)
    {
      // write obj to stream
      for(int i = 0; i < obj.size_; i++){
        os << obj[i] << ",";
      }
      // os << std::endl;
      return os;
    }

private:
    int size_;
    int* array_;
};

int main() {
    DumbArray arr(5);
    for(int i=0; i< 5; i++){
        arr[i] = i;
    }
    std::cout << "arr : " << arr << std::endl;
    DumbArray arr2;
    arr2 = arr;
    std::cout << "arr2 : "  << arr2 << std::endl;

    DumbArray arr3;
    arr3 = std::move(arr2);
    std::cout << "arr2 : "  << arr2 << std::endl;
    std::cout << "arr3 : "  << arr3 << std::endl;

    DumbArray arr4(std::move(arr3));
    std::cout << "arr3 : "  << arr3 << std::endl;
    std::cout << "arr4 : "  << arr4 << std::endl;
}