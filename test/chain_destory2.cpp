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
		std::cout << "Destroy Student " << name << std::endl;
		//printf("Destroy Student\n");
	}
};


 



class School {
private:
	void * buffer;
	Student *classs1;
	Student *classs2;
	Student *classs3;
	Student *lili;
	Student xiaoming;
	// std::vector<Student> classs;
public:

	
	School(){
		buffer = calloc(2, sizeof(Student));
		

		classs1 = new  Student[2];
		classs1[0].name = "classs1 A";
		classs1[1].name = "classs1 B";


		classs2 = (Student *) calloc(2, sizeof(Student));
		classs2[0].name = "classs2 A";
		classs2[1].name = "classs2 B";

		classs3 = new (buffer) Student[2]; // use buffer array
		classs3[0].name = "classs3 A";
		classs3[1].name = "classs3 B";

		lili = new Student();
		lili->name = "lili";

		xiaoming.name = "xiaoming";
	}

	~School() {
		printf("Destroy School\n");
		
		delete [] classs1;

		free(classs2);

		delete lili;	

		// invalide 3
		// for(int i = 0; i < 2; i++) {
		// 	delete &(classs3[i]);
		// }
		// delete [] classs3;
		 free(buffer);
		// invalide 3 end
		
		
		
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