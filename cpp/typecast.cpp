#include <iostream>
using std::ostream;
using std::istream;
using namespace std;
/**
 * dynamic_cast 子类转换为父类。 static_cast 同类之间相互转换。
 */
class Animal {
protected:
	string name;
public:

	Animal() {name="Animal";}
	string getName(){ return name;};
	virtual void run() const{};
};

class Cat : public Animal {
public:
	Cat() {name="Cat";}
	virtual void run() const{};
	 
};

class Dog : public Animal {
public:
	Dog() {name="Dog";}
	virtual void run() const{};
};

class Plant {
public:
	Plant() {}
};

class Tree : public Plant {
public:
	Tree() {}
};

class Flower : public Plant {
public:
	Flower() {}
};



int main() {
	
}