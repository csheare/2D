include<iostream>
#include<cstring>
#include<vector>

class Student:public Person{
public:
  Student():Person(),study(new char[1]);
  Student(const char*n,const char*m);
  virtual~Student(){delete []study;}
  virtual void display() const {
    std::cout<<Person::getName()<<","<<study<<std::endl;
  }
private:
  char*study;
  Student(const Student& s): study(new char(strlen(s.study + 1)){
	strcpy(study, s.study)
  }
  Student& operator=(const Student& s){
	if(this == s&){
		return *this;
	}
	delete [] study;
	study = new char(strlen(s.study + 1));
	strcpy(study, s.study);
	return *this;
 }	
};




int main(){
  std::vector<Person*>people;
  people.push_back(new Student("PeterQuill","Math"));
  people.push_back(new Person("PeterParker"));
}

