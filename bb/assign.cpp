#include <iostream>

class string{
public:
	string(){ std::cout<<"default"<<std::endl;}
	string(const char* b){std::cout<<"convert"<<std::endl;}
	string(const string& b){std::cout<<"copy"<<std::endl;}
	~string(){std::cout<<"destructor"<<std::endl;}
	string& operator=(const string&){
		std::cout<<"assign"<<std::endl;
		return *this;
	}
private:
	char * buf; 
};

class TestAssign{
public:
	TestAssign(char*n){name = n;}
private:
	string name;
};

class TestAssign2{
public:
	TestAssign2(char*n):name2(n){}
private:
	string name2;
};


int main(){
	TestAssign name("dog");
	TestAssign2 name2("cat");
	return 0;
}
