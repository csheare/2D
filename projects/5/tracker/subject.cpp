#include "Subject.h"
#include "Observer.h"
#include "gamedata.h"
#include "renderContext.h"

Subject::Subject():
  observers()
{ }



void Subject::detach( Observer* o ) {
  std::list<Observer*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {

      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Subject::update(Uint32 ticks) {
  std::list<Observer*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
}
