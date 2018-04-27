#include "bullet.h"
#include "bullets.h"
#include <cmath>
#include "ioMod.h"
#include "imageFactory.h"
#include "collisionStrategy.h"


Bullets::Bullets(const std::string&name, const Vector2f&pos, const Vector2f&vel):
  name(name),
  myVelocity(
    Gamedata::getInstance().getXmlInt(name+"/speedX"),
    Gamedata::getInstance().getXmlInt(name+"/speedY")
  ),
  bulletImages(ImageFactory::getInstance().getImages(name)),
  freeList(),
  bulletList(),
  strategy( new RectangularCollisionStrategy()),
  numBullets(Gamedata::getInstance().getXmlInt("numOfBullets"))
  {
    for(int i = 0; i< numBullets;i++){
      freeList.push_back(Bullet(name,pos,vel));
    }
}

Bullets::Bullets(const Bullets &b):
  name(b.name),
  myVelocity(b.myVelocity),
  bulletImages(b.bulletImages),
  freeList(b.freeList),
  bulletList(b.bulletList),
  strategy(b.strategy),
  numBullets(Gamedata::getInstance().getXmlInt("numOfBullets"))
  {}

void Bullets::draw() const{
  for(const auto& bullet : bulletList){
    bullet.draw();
  }
}

void Bullets::update(Uint32 ticks){
  std::list<Bullet>::iterator itr = bulletList.begin();
  while(itr != bulletList.end()){
    (itr)->update(ticks);
    if((itr)->goneTooFar()){
      freeList.push_back(*itr);
      itr = bulletList.erase(itr);
    }else{
      itr++;
     }
  }
}
void Bullets::shoot(const Vector2f& pos, const Vector2f& objVel){
  if(freeList.empty()){
    Bullet b(name, pos,objVel);
    bulletList.push_back(b);
   }else{
      Bullet b = freeList.front();
      freeList.pop_front();
      b.reset();
      b.setVelocity(objVel);
      b.setPosition(pos);
      bulletList.push_back(b);
  }
}


bool Bullets::collided(const Drawable*obj) const{
    for(const auto& bullet: bulletList){
      if(strategy->execute(bullet,*obj)){
        return true;
      }
    }
    return false;
}
