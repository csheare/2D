#ifndef OBSERVER__H
#define OBSERVER__H
#include <string>

class Observer{
public:
  Observer(const std::string&, const Vector2f& pos, int w, int h);
  Observer(const Observer&);
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
