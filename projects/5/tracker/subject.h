#ifndef SUBJECT__H
#define SUBJECT__H

#include <string>
#include <list>
#include <cmath>

class Observer;

class Subject {
public:

  //Todo:Finish these constructors
  Subject(): observers(){}
  Subject(Subject&s):
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
