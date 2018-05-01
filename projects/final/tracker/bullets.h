#ifndef BULLETS_H
#define BULLETS_H

#include "drawable.h"
#include "bullet.h"
#include <list>
#include <vector>

class CollisionStrategy;

class Bullets{
public:

  Bullets(const std::string&name, const Vector2f&pos, const Vector2f&vel);
  Bullets(const Bullets &);
  Bullets& operator=(const Bullets&) = delete;
  ~Bullets(){};
  void draw() const;
  void update(Uint32 ticks);
  void shoot(const Vector2f& pos, const Vector2f& objVel);//can adjust speed of Bulletss relative to player


  unsigned int BulletCount() const { return bulletList.size();}
  unsigned int freeCount() const { return freeList.size();}
  bool shooting() const { return !bulletList.empty();}
  bool collided(const Drawable*) const;


private:

  std::string name;
  Vector2f myVelocity;
  std::vector<Image*> bulletImages;
  std::list<Bullet> freeList;//used Bullet*
  std::list<Bullet> bulletList;
  //std::list<Bullet*> allBullets;
  CollisionStrategy * strategy;
  int numBullets;

};

#endif
