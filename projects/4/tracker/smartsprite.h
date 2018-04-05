#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include "twowaysprite.h"

class SmartSprite : public TwoWaySprite {
public:
  SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { }

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
