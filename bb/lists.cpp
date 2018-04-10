#include<iostream>
#include<cstring>
#include<list>
#include<map>
#include<vector>

int main(){
std::map<std::string,int> map;
std::list<int> list;
map["A"] = 1;


std::vector<int> vec;
vec.reserve(2);
std::vector<int> vec2(2);


std::cout<< vec.capacity() <<std::endl;
std::cout<< vec2.capacity() <<std::endl;

std::cout<< map["A"] <<std::endl;
//map["B"] = 2;


//std::cout<< map <<std::endl;


}
