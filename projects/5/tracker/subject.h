#ifndef SUBJECT__H
#define SUBJECT__H

#include <string>
#include <list>
#include <cmath>
#include "drawable.h"
#include "observer.h"
#include "twowaysprite.h"
#include "player.h"


class Subject : public Player{
public:

  Subject(const std::string& name);
  Subject(const Subject&s);
  virtual void update(Uint32 ticks);

  void attach( Observer* o ) { observers.push_back(o); }

  void detach( Observer* o );
  //need alert function
  virtual ~Subject() {}


protected:

  std::list<Observer*> observers;

  Subject& operator=(const Subject&);

};
#endif
