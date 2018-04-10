#include <iostream>
#include <string.h>
#include <vector>
//always use initialization lists over assignment
class Pokemon{
public:
Pokemon(): hp(0), name(new char(strlen("Pidgey") + 1)){
    strcpy(name, "Pidgey");
    std::cout << "default"<< std::endl;
}//default
Pokemon(int x): hp(x), name(new char(strlen("Pidgey") + 1)){
    strcpy(name, "Pidgey");
    std::cout << "convert1"<< std::endl;
}//default
Pokemon(int x, const char* n): hp(x), name(new char[strlen(n) + 1]){
  strcpy(name,n);
  std::cout << "covert2" << std::endl;
}//convert
Pokemon(const Pokemon& p): hp(p.hp), name(new char(strlen(p.name) + 1)){//copy
  strcpy(name, p.name);//need deep copy
  std::cout << "copy" << std::endl;
}
//destructor
Pokemon & operator=(const Pokemon& rhs){
  std::cout << "assign" << std::endl;
  if(this == &rhs) return *this;// need & for referance
  delete [] name;// name is an array of chars
  name = new char(strlen(rhs.name) + 1);
  strcpy(name, rhs.name);
  this->hp = rhs.hp;
  return *this;//return the new value of this to
  //? why is this a pass by value to a refernce return value
}
int getHp() const{ return hp;}
const char* getName() const{ return name;}

private:
int hp;
char* name;
};
std::ostream& operator<<(std::ostream& out, const Pokemon & p){
  return out<< p.getHp() <<" "<< p.getName();
}
//output operator

int main(){

//Pokemon d;//don;t do Pokemon d()
//Pokemon c(4,"Courtney");
//Pokemon j(10,"Jeff");
//Pokemon m(j);
//c = j;//will call assignment
//Pokemon s = j;//this will call copy constructor

//std::cout << s << std::endl;

//vector testing
std::vector<Pokemon> vec;//don't do vec(2)
for(unsigned int i=0; i < 4; i++){
  //vec.emplace_back(i);
}

std::cout << "Vec 2 processing..."<< std::endl;

std::vector<Pokemon> vec2;//don't do vec(2)
//vec2.reserve(2);
for(unsigned int i=0; i < 4; i++){
  vec2.push_back(i);
}
//won't need final copy

}
