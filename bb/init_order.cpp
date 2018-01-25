#include<iostream>

class Student{
	public:
		Student(int a): age(a), iq(a+100){}
	//private:
		int iq;
		int age;
};

int main(){

	Student *s = new Student(5);
	std::cout << s->iq << " " << s->age << std::endl;
	return 0;

}
