#include "subject.h"
#include "observer.h"
#include "gamedata.h"
#include "twowaysprite.h"



Subject::Subject(const std::string& name):
  Player(name),
  observers()
{ }

Subject::Subject(const Subject& s) :
  Player(s),
  observers( s.observers )
  { }


void Subject::detach( Observer* o ) {
  auto ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Subject::update(Uint32 ticks) {
  Player::update(ticks);
  auto ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
}
