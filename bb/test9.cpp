#include<cstring>
#include<iostream>

class Pokemon{
public:
  Pokemon(const char*n):name(new char[strlen(n)+1]){
    strcpy(name,n);
  }
  const char * getName() const {

	return name;
  }
private:
  char*name;
};
std::ostream& operator<<(std::ostream& out, const Pokemon& p){

	return out << p.getName() ;

}
int main(){
  Pokemon poke("Snorlax");
  std::cout<<poke<<std::endl;
}

