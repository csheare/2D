#ifndef PLAYER__H
#define PLAYER__H

#include "twowaysprite.h"
#include "drawable.h"
#include "bullets.h"
#include "bullet.h"
#include "renderContext.h"

class ExplodingSprite;

class Player : public TwoWaySprite{
public:
  Player(const std::string& n);
  Player(const Player& s);
  ~Player();
  void advanceFrame(Uint32);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void shoot();

  virtual void incrFrame() { currentFrame = (currentFrame+1) % numberOfFrames;}
  //this is for pool hud
  unsigned int bulletCount() const { return bullets.BulletCount();}
  unsigned int freeCount()   const { return bullets.freeCount();}


  virtual void draw() const;
  virtual void update(Uint32 ticks);

  Bullets getBullets() const {
    return bullets;
  }

  virtual void explode();



  void right();
  void left();
  void up();
  void down();
  void stop();

private:

  Uint32 delay = 0;
  ExplodingSprite* explosion;
  const std::vector<Image*> imagesShootLeft;
  const std::vector<Image*> imagesShootRight;
  bool collision;

  Vector2f initialVelocity;

  float minFrameDelay;
  float frameDelay;
  unsigned frameSpeed;
  float timeSinceLastImage;

  //Data Attributes that descibe Bullets

  std::string bulletName;
  float bulletInterval;
  float timeSinceLastBullet;
  float minBulletSpeed;
  Bullets bullets;

  enum FACE { LEFT, RIGHT};
  FACE facing;

};
#endif
