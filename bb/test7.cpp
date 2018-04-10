#include<cstdlib>
#include<vector>
#include<iostream>

void display(const std::vector<int >& numbers){
  for(auto n:numbers){
    std::cout<<n<<std::endl;
  }
}
void display2(const std::vector<int> & numbers){
	std::vector<const int*>::const_iterator  i = numbers.begin();
	while(i != numbers.end()){
		std::cout<<*i<<std::endl;
		i++;
	}
}





int main(){
  std::vector<int >numbers;
  numbers.reserve(5);
  for(unsigned int i=0;i<5;++i){
    numbers.push_back(rand()%100);
  }
  display2(numbers);
}

