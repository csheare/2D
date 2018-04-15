#ifndef PLAYER__H
#define PLAYER__H

#include "drawable.h"
#include "subject.h"


// In this example the player is derived from MultiSprite.
// However, there are many options.
class Player : public Subject, public Drawable {
public:
  Player();
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
