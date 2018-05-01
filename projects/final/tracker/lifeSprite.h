#ifndef LIFESPRITE__H
#define LIFESPRITE__H
#include <string>
#include "drawable.h"

class CollisionStrategy;

class LifeSprite : public Drawable{
public:
  LifeSprite(const std::string&);
  LifeSprite(const std::string&, const Vector2f& pos, const Vector2f& vel,
         const Image*);
  LifeSprite(const LifeSprite&);
  virtual ~LifeSprite();
  LifeSprite& operator=(const LifeSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { return image; }
  virtual const SDL_Surface* getSurface() const {
    return image->getSurface();
  }
  int getScaledWidth()  const { return getScale()*image->getWidth();  }
  int getScaledHeight() const { return getScale()*image->getHeight(); }
  virtual int getWorldWidth() const {return worldWidth;}
  virtual int getWorldHeight() const {return worldHeight;}
  bool isActive(){return active;}
  void toggle() { active = !active;}
  bool collided(const Drawable*) const;
  void setDelay(int d){ delay = d;}
  int getDelay(){return delay;}
  void decrementDelay(){ delay--;}
  void stop(){ active = false;}

private:
  const Image * image;

protected:
  int worldWidth;
  int worldHeight;
  bool active;
  CollisionStrategy * strategy;
  Uint32 delay;

  int getDistance(const LifeSprite*) const;
  Vector2f makeVelocity(int, int) const;
};
#endif
