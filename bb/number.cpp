#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <list>
#include <functional>

const int MAX = 20;
const int MAX_NUMBER = 100;

// TODO:
// init list
// print numberList
// use vectors and lists
// search and sort
// lambdas vs object functions

//TODO:
// 1) search with lists, vector, and maps Done: check
// 2) sort with lists, vector, and maps Done:
// lambdas and object functions Done:

// [capture clause] (parameters) -> return-type {body}


class Number{
public:
  //constructors
  //default
  Number(): number(0){}
  //convert
  Number(int x): number(x){}
  //copy
  Number(const Number& n): number(n.number){}
  //get number
  int getNumber()const{
    return number;
  }
  //overload comparison
  // bool operator<(const Number & rhs)const{
  //   return number < rhs.number;
  // }
  // bool operator>(const Number& rhs) const{
  //   return number > rhs.number;
  // }
  Number& operator=(const Number& rhs){
    if(this == &rhs){ return *this;}
    this->number = rhs.getNumber();
    return *this;
  }
private:
  int number;
};
//output operator
std::ostream & operator<<(std::ostream& out, const Number & num){
  return out << num.getNumber();
}

void init(std::list<Number > & numberList){
  for(unsigned int i=0;i< MAX; i++){
    numberList.push_back(Number(rand()% MAX_NUMBER));
  }
}
void init(std::list<Number*> & numberList){
  for(unsigned int i=0;i< MAX; i++){
    numberList.push_back(new Number(rand()% MAX_NUMBER));
  }
}
void init(std::list<int> & numberList){
  for(unsigned int i=0;i< MAX; i++){
    numberList.push_back(rand()% MAX_NUMBER);
  }
}


void initmap(std::vector<std::string> & vec, std::map<std::string, int> & map){
  for (const auto & n : vec){
    map[n] = rand() % MAX_NUMBER;
  }
}

void printMap(const std::map<std::string,int> & map){
  for (const auto & item : map){
    std::cout << item.first << " "<< item.second << std::endl;
  }
  std::cout << std::endl;
}
void printInts(const std::list<int> nums){
  for(int i : nums){
    std::cout << i << ' ';
  }
  std::cout << '\n';
}


// with iterator
void printIter(const std::list<Number*> & numberList){
  std::list<Number*>::const_iterator iter = numberList.begin();
  while(iter != numberList.end()){
    std::cout << **iter << " ";
    iter++;
  }
  std::cout << std::endl;
}

// with auto for loop
void printFor(const std::list<Number> & numberList){

  for( auto num : numberList){
    std::cout << num << " ";
   }
   std::cout << std::endl;
}

bool isFound(std::vector<std::string> &names, std::map<std::string, int> &map, int index){
  return map.find(names.at(index)) != map.end();

}

class Target{
public:
  Target(int x) : number(x){}
  bool operator()(const Number * rhs) const{
    return number == rhs->getNumber();
  }
private:
  int number;
};

class NumberLess{
public:
  bool operator()(const Number* a, const Number* b){
    return a->getNumber() < b->getNumber();
  }
};


int main(){

  //1) Lists
  std::list<Number*> numberList;
  // a)initialize
  init(numberList);

  //b)print
  printIter(numberList);

  //c)find
  // Number n(49);
  // auto iter = find_if(numberList.begin(),numberList.end(),Target(n.getNumber()));
  // if(iter == numberList.end()){
  //   std::cout << "BOO" << '\n';
  // }else{
  //   std::cout << "YAY" << '\n';
  // }

  //3) maps, search for something in a map
      // a)initialize
      // srand( time(0) );
      // std::vector<std::string> names;
      // names.push_back("Red Oak");
      // names.push_back("Sugar Maple");
      // names.push_back("Chestnut");

      //std::vector<std::string> names = {"Bob", "Debby", "Ron"};

      //std::map<std::string, int> mymap;
      //initmap(names, mymap);
      // b)print
      //printMap(mymap);

    // c)find
    // if(isFound(names, mymap, 2)){
    //   std::cout << "YOOOO" << '\n';
    // }else{
    //   std::cout << "BOOO" << '\n';
    // }

    ///sorting
    //lists
      //ints
    // std::list<int> num;
    // init(num);
    // printInts(num);
    // num.sort();
    // printInts(num);
    //   //objects
    // std::list<Number> numObjs;
    // init(numObjs);
    // printFor(numObjs);
    // numObjs.sort();
    // printFor(numObjs);
    //   //ptrs
    // std::list<Number*> numPtrs;
    // init(numPtrs);
    // printIter(numPtrs);
    NumberLess nl;

    numberList.sort(
      [](const Number * a, const Number * b)->bool{return a->getNumber() > b->getNumber();}
    );

    //why does passing NumberLess() work?

    printIter(numberList);
    std::cout << nl(new Number(10), new Number(6)) << '\n';

  }
