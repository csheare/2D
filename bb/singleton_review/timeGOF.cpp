//1. Place constructors and assignment in private section.
//2. Declare a static instance variable as a data attribute of the class
//3. Define the static instance variable somewhere in the anonymous
//   namespace.
//4. Define a static class member function to access the instance variable.

#include <stdlib.h>
#include <iostream>
#include <string.h>

class CounterG{
public:
	static CounterG* getInstance();
	char * getName() const{
		return name;
	}
	int getCount() const{
		return count;
	}

private:
	static CounterG * instance;
	CounterG(): count(0) , name(new char(strlen("Default") + 1)){
                strcpy(name, "Default");
                std::cout<<"default"<<std::endl;
        }
        //copy
        // CounterG(const CounterG& c): count(c.count), name(new char(strlen(c.name)+1)){
        //         strcpy(name, c.name);
        //         std::cout<< "copy"<<std::endl;
        // }
        // CounterG(int x,const char * n): count(x), name(new char(strlen(n)+1)){
        //         strcpy(name, n);
        //         std::cout<<"convert"<<std::endl;
        // }
	CounterG & operator=(const CounterG & rhs){
		std::cout<<"assign"<<std::endl;
		if(this == &rhs){
			return *this;
		}
		delete []  name;
		name = new char(strlen(rhs.name)+1);
		strcpy(name, rhs.name);
		this->count = rhs.count;
		return *this;
	}
	~CounterG(){
		delete [] name;
	}

	int count;//number of times instance is touched
	char * name;

};
std::ostream& operator<<(std::ostream& out, const CounterG& c){

		return out << "Name is: "<< c.getName() <<", Count is: " << c.getCount();
}

//declare outside of class
//The Gof singleton requires that you have a private instance of the Class, and that
//you allocate space in the heap by using the new key word
CounterG * CounterG::getInstance(){
	if(!instance) instance = new CounterG;
	return instance;
}

CounterG* CounterG::instance = NULL;


int main(){
	CounterG * cg1 = CounterG::getInstance();
	CounterG * cg2 = CounterG::getInstance();
	std::cout<<*cg1<<std::endl;
	std::cout<<*cg2<<std::endl;
}
