//1. Place constructors and assignment in private section.
//2. Declare a static instance variable as a data attribute of the class
//3. Define the static instance variable somewhere in the anonymous
//   namespace.
//4. Define a static class member function to access the instance variable.

#include <iostream>
#include<stdlib.h>
#include<string.h>

class CounterM{
public:
	static CounterM& getInstance();
	int getCount()const{
		return count;
	}
	const char * getName()const{
		return name;
	}
	
private:
	int count;
	char * name;
	//default
	CounterM(): count(0), name(new char(strlen("Default")+1)){
		strcpy(name,"Default");
	}
	CounterM(const CounterM& c): count(c.count), name(new char(strlen(c.name)+1)){
		strcpy(name,c.name);
	}
	CounterM(int x, char * c): count(x), name(new char(strlen(c)+1)){
		strcpy(name, c);
	}
	CounterM& operator=(const CounterM& c){

		if(this == &c){
			return *this;
		}
		count = c.count;
		delete []  name;
		name = new char(strlen(c.name)+1);
		strcpy(name, c.name);
		return *this;
	}
	
};
std::ostream& operator<<(std::ostream & out, const CounterM& c){

	return out << c.getCount() << c.getName();
}

//define outtside of class
//This different from the GoF method because there is no need to have a private member
//variable for the class, nor a need to allocate space on the heap with a new key word 
CounterM& CounterM::getInstance(){
	static CounterM instance;
	return instance;
}


int main(){
	
	CounterM& cm1 = CounterM::getInstance();
	std::cout<< cm1 <<std::endl;
}



