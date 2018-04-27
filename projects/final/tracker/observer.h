#ifndef OBSERVER__H
#define OBSERVER__H
#include <SDL.h>
#include <string>
#include "vector2f.h"
#include "drawable.h"
#include "twowaysprite.h"

class Observer: public TwoWaySprite {
public:

  Observer(const std::string& name,const Vector2f& pos,int w, int h);
  virtual ~Observer() { }

  void update(Uint32 ticks);

  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  Vector2f makeVelocity(int, int) const;


private:
  enum MODE {NORMAL, EVADE};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
