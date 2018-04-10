#include <iostream>

class Clock{
public:
	static Clock* getInstance();
	int getTicks() const { return ticks; }
	void update(){ ++ticks;}
private:
	static Clock* instance;
	Clock() : ticks(0){};
	int ticks;
};
Clock* Clock::getInstance(){
	if(!instance) instance = new Clock;
	return instance;
}

Clock* Clock::instance = NULL;

int main(){
	Clock* clock = Clock::getInstance();
	clock->update();
	std::cout << clock->getTicks() << std::endl;
}
