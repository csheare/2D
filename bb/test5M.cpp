#include <iostream>

class Clock{
public:
	static Clock& getInstance();
        int getTicks() const { return ticks; }
        void update(){ ++ticks;}
private:
	Clock() : ticks(0){}
        int ticks;
};
Clock& Clock::getInstance(){
	static Clock instance;
	return instance;
}

int main(){
        Clock& clock = Clock::getInstance();;
        clock.update();
        std::cout << clock.getTicks() << std::endl;
}
