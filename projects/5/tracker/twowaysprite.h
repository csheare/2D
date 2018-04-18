#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "multisprite.h"
#include "drawable.h"

class TwoWaySprite : public MultiSprite {
public:
  TwoWaySprite(const std::string&);
  TwoWaySprite(const TwoWaySprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const {
    return images[currentFrame];
  }
  void setImagesRight();
  void setImagesLeft();

  int getScaledWidth()  const {
    return getScale()*images[currentFrame]->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*images[currentFrame]->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return images[currentFrame]->getSurface();
  }

  virtual int getWorldWidth() const {return worldWidth;}
  virtual int getWorldHeight()  const{return worldHeight;}

  // float getMinFrameDelay() const{ return minFrameDelay;}
  // void setMinFrameDelay(float x){ minFrameDelay = x; }
  //
  // float getFrameDelay() const{return frameDelay;}
  // void setFrameDelay(float x){frameDelay = x;}
  //
  // unsigned getFrameSpeed() const{ return frameSpeed;}
  // void setFrameSpeed(unsigned x){ FrameSpeed = x; }

  unsigned getCurrentFrame() const{ return currentFrame;}
  void setCurrentFrame(unsigned x){ currentFrame = x;}

  unsigned getNumberOfFrames() const { return numberOfFrames;}
  void setNumberOfFrames(unsigned x){ numberOfFrames = x;}

  unsigned getFrameInterval() const { return frameInterval;}
  void setFrameInterval(unsigned x){ frameInterval = x;}

  float getTimeSinceLastFrame() const { return timeSinceLastFrame;}
  void setTimeSinceLastFrame(float x){ timeSinceLastFrame =x;}






protected:
  std::vector<Image*> images;
  std::vector<Image *> imagesRight;
  std::vector<Image *> imagesLeft;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  virtual void advanceFrame(Uint32 ticks);
  TwoWaySprite& operator=(const TwoWaySprite&);
  Vector2f makeVelocity(int, int) const;
};
#endif
