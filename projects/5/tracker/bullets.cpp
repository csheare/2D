#include "bullet.h"
#include "bullets.h"
#include <cmath>
#include "ioMod.h"
#include "imageFactory.h"
#include "collisionStrategy.h"


Bullets::~Bullets(){
  // for(auto b : BulletList){
  //   delete b;
  // }
}

Bullets& Bullets::operator=(const Bullets& rhs){
  if(this == &rhs) return *this;
  this->name = rhs.name;
  this->myVelocity = rhs.myVelocity;
  this->BulletImages = rhs.BulletImages;
  this->freeList = rhs.freeList;
  this->BulletList = rhs.BulletList;
  delete this->strategy;


  CollisionStrategy* pp = dynamic_cast<PerPixelCollisionStrategy*>(rhs.strategy);
  if(pp){
    this->strategy = new PerPixelCollisionStrategy();
  }

  CollisionStrategy* r = dynamic_cast<RectangularCollisionStrategy*>(rhs.strategy);
  if(r){
    this->strategy = new RectangularCollisionStrategy();
  }

  CollisionStrategy* mp = dynamic_cast<MidPointCollisionStrategy*>(rhs.strategy);
  if(mp){
    this->strategy = new MidPointCollisionStrategy();;
  }

  return *this;
}

Bullets::Bullets(const std::string&name, const Vector2f&pos, const Vector2f&vel):
  name(name),
  myVelocity(
    Gamedata::getInstance().getXmlInt(name+"/speedX"),
    Gamedata::getInstance().getXmlInt(name+"/speedY")
  ),
  BulletImages(ImageFactory::getInstance().getImages(name)),
  freeList(),
  BulletList(),
  strategy(NULL),
  numBullets(Gamedata::getInstance().getXmlInt("numOfBullets"))
  {
    const string thisStrategy = Gamedata::getInstance().getXmlStr("collisionStrategy");
    if(thisStrategy == "PerPixel"){
      strategy = new PerPixelCollisionStrategy();
    }else if(thisStrategy == "Rectangular"){
      strategy = new RectangularCollisionStrategy();
    }else if(thisStrategy == "MidPoint"){
      strategy = new MidPointCollisionStrategy();
    }

    for(int i = 0; i< numBullets;i++){
      freeList.push_back(new Bullet(name,pos,vel));
    }
}

Bullets::Bullets(const Bullets &b):
  name(b.name),
  myVelocity(b.myVelocity),
  BulletImages(b.BulletImages),
  freeList(b.freeList),
  BulletList(b.BulletList),
  strategy(b.strategy),
  numBullets(Gamedata::getInstance().getXmlInt("numOfBullets"))
  {}

void Bullets::draw() const{
  for(const auto& Bullet : BulletList){
    Bullet->draw();
  }

}
void Bullets::update(Uint32 ticks){
  std::list<Bullet*>::iterator itr = BulletList.begin();
  while(itr != BulletList.end()){
    (*itr)->update(ticks);
    if((*itr)->goneTooFar()){
      freeList.push_back(*itr);
      itr = BulletList.erase(itr);
    }else{
        itr++;
    }
  }
}
void Bullets::shoot(const Vector2f& pos, const Vector2f& objVel){
  if(freeList.empty()){
    BulletList.push_back(new Bullet(name, pos,objVel));
  }else{
    Bullet * b = freeList.front();
    freeList.pop_front();
    b->reset();
    b->setVelocity(objVel);
    b->setPosition(pos);
    BulletList.push_back(b);
  }
}

bool Bullets::collided(const Drawable*obj) const{
  auto it = BulletList.begin();
  while(it != BulletList.end()){
    if(strategy->execute(**it,*obj)){
      return true;
    }
    ++it;
  }
  return false;
}
