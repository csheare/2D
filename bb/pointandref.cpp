
#include <stdlib.h>
#include <iostream>
int main(){

int num = 88;
int num2 = 103;
int *ptr = &num;
int & ref = num;
*ptr += 2;
ref = num2;
ptr = &num2;
std::cout << num << std::endl;
std::cout << *ptr << std::endl;
std::cout << ref << std::endl;

}



