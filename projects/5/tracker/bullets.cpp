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
  this->bulletImages = rhs.bulletImages;
  this->freeList = rhs.freeList;
  this->bulletList = rhs.bulletList;
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
  bulletImages(ImageFactory::getInstance().getImages(name)),
  freeList(),
  bulletList(),
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
      freeList.emplace_back(Bullet(name,pos,vel));
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
    (*itr).update(ticks);
    if((*itr).goneTooFar()){
      freeList.push_back(*itr);
      itr = bulletList.erase(itr);
    }else{
        itr++;
    }
  }
}
void Bullets::shoot(const Vector2f& pos, const Vector2f& objVel){
  std::cout << "Shoot Bullet" << std::endl;
  if(freeList.empty()){
   Bullet b(name, pos,objVel);
    bulletList.push_back(b);
   }else{
      Bullet b = freeList.front();
      freeList.pop_front();
      b.reset();
      b.setVelocity(objVel);
      b.setPosition(pos);
      bulletList.emplace_back(b);
  }
}


bool Bullets::collided(const Drawable*obj) const{
    for(const auto& Bullet: bulletList){
      if(strategy->execute(Bullet,*obj)){
        return true;
      }
    }
    return false;
  }
