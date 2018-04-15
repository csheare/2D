#ifndef PLAYER__H
#define PLAYER__H

#include "twowaysprite.h"
#include "subject.h"

class Player : public Subject, public TwoWaySprite{
public:
  Player(const std::string& n);
  Player(const Player& s);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();
  void stop();
private:
  bool collision;
  Vector2f initialVelocity;
};
#endif
