#ifndef BULLET_H
#define BULLET_H


#include "sprite.h"

class Bullet : public Sprite{

public:
  Bullet(const std::string&, const Vector2f&, const Vector2f&);
  Bullet(const Bullet&);
  virtual void update(Uint32 ticks);
  bool goneTooFar() const{ return tooFar;}
  void reset();
  Bullet& operator=(const Bullet&) =delete;

private:
  float distance;
  float maxDistance;
  bool tooFar;

};

#endif
