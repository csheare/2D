#include "subject.h"
#include "observer.h"
#include "gamedata.h"
#include "renderContext.h"

Subject::Subject(Drawable *s):
  observers(),
  drawable(s)
{ }

Subject::Subject(const Subject& s) :
  observers( s.observers ),
  drawable(s.drawable)
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
    (*ptr)->setPlayerPos( getDrawable()->getPosition() );
    ++ptr;
  }
}
Drawable* Subject::getDrawable(){
  return drawable;
}
