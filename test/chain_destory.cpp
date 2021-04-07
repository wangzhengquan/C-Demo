#include <stdio.h>
#include <string.h>
#include "usg_common.h"
#include <vector>

// class Student {
// private:
// 	std::string name;
// public:
// 	Student() {}
// 	Student(const std::string &n): name(n) {

// 	}

// 	~Student() {
// 		std::cout << "Destroy Student " << name << std::endl;
// 	}
// };





struct Student {
	std::string name;
  

	~Student() {
		//std::cout << "Destroy Student " << name << std::endl;
		printf("Destroy Student\n");
	}
};


class School {
private:
	std::string name;
	Student xiaoming;
public:

	
	School(){
		name = "yuying";
		xiaoming.name = "xiaoming";
	}

	~School() {
		printf("Destroy School\n");
	}
};


void mytest() {
	printf("test begin\n");
	School School;
	printf("test end\n");
}
 

int main() {
	mytest();
}