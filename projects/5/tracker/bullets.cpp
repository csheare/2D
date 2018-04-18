#include "bullet.h"
#include "bullets.h"
#include <cmath>
#include "ioMod.h"
#include "imageFactory.h"
#include "collisionStrategy.h"


Bullets::~Bullets(){
}

Bullets::Bullets(const std::string&n):
  name(n),
  myVelocity(
    Gamedata::getInstance().getXmlInt(name+"/speedX"),
    Gamedata::getInstance().getXmlInt(name+"/speedY")
  ),
  BulletImages(ImageFactory::getInstance().getImages(name)),
  freeList(),
  BulletList(),
  strategy(NULL)
  {
    const string thisStrategy = Gamedata::getInstance().getXmlStr("collisionStrategy");
    if(thisStrategy == "PerPixel"){
      strategy = new PerPixelCollisionStrategy();
    }else if(thisStrategy == "Rectangular"){
      strategy = new RectangularCollisionStrategy();
    }else if(thisStrategy == "MidPoint"){
      strategy = new MidPointCollisionStrategy();
    }

}
Bullets::Bullets(const Bullets &b):
  name(b.name),
  myVelocity(b.myVelocity),
  BulletImages(b.BulletImages),
  freeList(b.freeList),
  BulletList(b.BulletList),
  strategy(b.strategy)
  {}

void Bullets::draw() const{
  for(const auto& Bullet : BulletList){
    Bullet.draw();
  }

}
void Bullets::update(Uint32 ticks){
  std::list<Bullet>::iterator itr = BulletList.begin();
  while(itr != BulletList.end()){
    itr->update(ticks);
    if(itr->goneTooFar()){
      freeList.push_back(*itr);
      itr = BulletList.erase(itr);
    }else{
          itr++;
    }
  }
}
void Bullets::shoot(const Vector2f& pos, const Vector2f& objVel){
  if(freeList.empty()){
    Bullet b(name, pos,objVel);
    BulletList.push_back(b);
  }else{
    Bullet b = freeList.front();
    freeList.pop_front();
    b.reset();
    b.setVelocity(objVel);
    b.setPosition(pos);
    BulletList.push_back(b);
  }
}

bool Bullets::collided(const Drawable*obj) const{
  for(const auto& Bullet: BulletList){
    if(strategy->execute(Bullet,*obj)){
      return true;
    }
  }
  return false;
}
