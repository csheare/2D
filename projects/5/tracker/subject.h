#ifndef SUBJECT__H
#define SUBJECT__H

#include <string>
#include <list>
#include <cmath>

class Observer;

class Subject {
public:

  virtual void update(Uint32 ticks);
  void attach( Observer* o ) { observers.push_back(o); }
  void detach( Observer* o );
  //need alert function


protected:
  std::list<Observer*> observers;
  Subject& operator=(const Subject&);
};
#endif
