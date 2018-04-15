#ifndef OBSERVER__H
#define OBSERVER__H
#include <SDL.h>
#include <string>
#include "vector2f.h"
#include "drawable.h"

class Observer: public Drawable{
public:

  Observer(Drawable* draw,const Vector2f& pos, int w, int h);
  virtual ~Observer() { }

  void update(Uint32 ticks);
  void draw() const;
  int getScaledWidth() const;
  int getScaledHeight() const;
  const SDL_Surface* getSurface() const;
  const Image* getImage() const;
  void setVelocityX(float vx);
  int getWorldWidth() const;
  int getWorldHeight() const;

  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  Vector2f makeVelocity(int, int) const;
  Drawable *getDrawable() const;

private:
  enum MODE {NORMAL, EVADE};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;
  Drawable * drawable;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
