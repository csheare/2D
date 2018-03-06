#1. Place constructors and assignment in private section.
#2. Declare a static instance variable as a data attribute of the class
#3. Define the static instance variable somewhere in the anonymous
#   namespace.
#4. Define a static class member function to access the instance variable.




#include <iostream>
#include<stdlib.h>

class CounterM{
public:
	static CounterM& getInstance();

private::
//default
};

//define outtside of class
//This different from the GoF method because there is no need to have a private member
//variable for the class, nor a need to allocate space on the heap with a new key word 
CounterM& CounterM::getInstance(){
	static CounterM instance;
	return instance;
}


int main(){

}
