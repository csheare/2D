#include <iostream>
#include <vector>
#include <string>

class Shape{
public:
Shape(const std::string & n): name(n){}
const std::string getName() const{ return name;}
virtual float area() const= 0;//this is private virtual

private:
std::string name;

};

class Circle: public Shape{
public:
Circle(const std::string & n,float r): Shape(n), radius(r){}
virtual float area() const { return (3.14 * radius * radius);}

private:
float radius;

};
void printAreasF(const std::vector<Shape*>& shapes) {//use a ranged for loop to print over values in shape, use cast as necessary
for( auto s : shapes){
	printf("Area: %f\n:",s->area());
}

}
void printAreasW(const std::vector<Shape*>& shapes){//Use a iterative while loop, use cast as necessary
std::vector<Shape*>::const_iterator iterator = shapes.begin();
while(iterator != shapes.end()){
	printf("Area: %f\n",(*iterator)->area());
	iterator++;
}
}


int main(){

std::vector<Shape*> shapes;
shapes.push_back(new Circle("circle",5.0));
printAreasF(shapes);
printAreasW(shapes);

}
