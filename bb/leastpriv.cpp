#include <iostream>

class string{
public:
	string(const char* n) : buf(new char[strlen(n) +1]){
		strcpy(buf,n);
	}
	const char* get() const{ return buf;}
private:
	char * buf;
};
std::ostream&
operator<<(std::ostream& out, const string& s){
	return out << s.get();
}

int main(){
	string x("Hello");
	std::cout << x.get() << std::endl;
}
