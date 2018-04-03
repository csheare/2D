#ifndef SUBJECTSPRITE__H
#define SUBJECTSPRITE__H

#include <string>
#include <list>
#include <cmath>
#include "twowaysprite.h"

class SmartSprite;

//I want to make this a Subject.h class using Templates

class SubjectSprite : public TwoWaySprite {
public:
  SubjectSprite(const std::string&);
  SubjectSprite(const SubjectSprite&);

  void update(Uint32 ticks);
  void attach( SmartSprite* o ) { observers.push_back(o); }
  void detach( SmartSprite* o );

protected:
  std::list<SmartSprite*> observers;
  SubjectSprite& operator=(const SubjectSprite&);
};
#endif
