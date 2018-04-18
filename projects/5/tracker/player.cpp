#include "player.h"
#include <cmath>
#include "twowaysprite.h"
#include "gamedata.h"


void Player::advanceFrame(Uint32 ticks){
  TwoWaySprite::advanceFrame(ticks);
  float speed = 3*getVelocity().magnitude();
  frameDelay += std::max(minFrameDelay, speed);
  if(frameDelay > frameSpeed){
    incrFrame();
    frameDelay =0;
  }
}

void Player::draw() const {
  bullets.draw();
  Uint32 x = static_cast<Uint32>(getX());
  Uint32 y = static_cast<Uint32>(getY());
  images[currentFrame]->draw(x,y);
}

void Player::update(Uint32 ticks){
  if ( !collision ){
       TwoWaySprite::update(ticks);
  }
  advanceFrame(ticks);
  timeSinceLastBullet += ticks;
  bullets.update(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if(getY() < 0){
    setVelocityY(std::abs(getVelocityY()));
  }
  if(getY() > worldHeight-getScaledHeight()){
    setVelocityY(-std::abs(getVelocityY()));
  }
  if(getX() < 0){
    setVelocityX(std::abs(getVelocityX()));
  }
  if(getX() > worldWidth - getScaledWidth()){
    setVelocityX(-std::abs(getVelocityX()));
  }
  if(getVelocityX() > 0){
    setImagesRight();
    facing = RIGHT;
  }
  if(getVelocityX() < 0){
    setImagesLeft();
    facing = LEFT;
  }
  else{
    if(facing == LEFT) setImagesLeft();
    else setImagesRight();
  }

  stop();
}



Player::Player(const std::string& name) :
  TwoWaySprite(name),
  imagesShootLeft(RenderContext::getInstance()->getImages(name + "L")),
  imagesShootRight(RenderContext::getInstance()->getImages(name)),
  collision(false),
  initialVelocity(getVelocity()),
  minFrameDelay(Gamedata::getInstance().getXmlFloat(name+"/minFrameDelay")),
  frameDelay(0),
  frameSpeed(Gamedata::getInstance().getXmlFloat(name+"/frameSpeed")),
  timeSinceLastImage(0),
  numBullets(Gamedata::getInstance().getXmlInt("numOfBullets")),
  bulletName(Gamedata::getInstance().getXmlStr(name+"/bulletName")),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName + "/frameSpeed")),
  timeSinceLastBullet(0),
  minBulletSpeed(Gamedata::getInstance().getXmlInt(bulletName + "/minSpeed")),
  bullets(bulletName),
  facing(RIGHT)
{
}

Player::Player(const Player& s) :
  TwoWaySprite(s),
  imagesShootLeft(s.imagesShootLeft),
  imagesShootRight(s.imagesShootRight),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  minFrameDelay(s.minFrameDelay),
  frameDelay(s.frameDelay),
  frameSpeed(s.frameSpeed),
  timeSinceLastImage(s.timeSinceLastImage),
  numBullets(s.numBullets),
  bulletName(s.bulletName),
  bulletInterval(s.bulletInterval),
  timeSinceLastBullet(s.timeSinceLastBullet),
  minBulletSpeed(s.minBulletSpeed),
  bullets(s.bullets),
  facing(RIGHT)
  { }

Player& Player::operator=(const Player& s) {
  TwoWaySprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::shoot(){
  if(getVelocityX()> 0){ images = imagesShootRight;}
  else if(getVelocityX() < 0){ images = imagesShootLeft;}
  else if ( facing == RIGHT){ images = imagesShootRight;}
  else if( facing == LEFT){ images = imagesShootLeft;}

  if(timeSinceLastBullet > bulletInterval){
    Vector2f vel = getVelocity();
    float x = 0;//questionable
    float y = getY() + getScaledHeight() / 4;
    if(vel[0] > 0){
      x = getX() + getScaledWidth();
      vel[0] += minBulletSpeed;
    }
    else if(vel[0] < 0 ){
      x = getX();
      vel[0] -= minBulletSpeed;
    }
    else if(facing == RIGHT){
      x = getX() + getScaledWidth();
      vel[0] += minBulletSpeed;
    }
    else if (facing == LEFT){
      x = getX();
      vel[0] -= minBulletSpeed;
    }
    bullets.shoot(Vector2f(x,y),vel);
    timeSinceLastBullet = 0;
  }
}

void Player::stop() {
  setVelocityX( 0.5*getVelocityX() );
  setVelocityY(0);
}


void Player::right() {
  if ( getX()  < getWorldWidth()-getScaledWidth() ) {
    setVelocityX(initialVelocity[0]);
    setImagesRight();//For Two Way
  }
}
void Player::left()  {
  if ( getX() > 0) {
     setVelocityX(-initialVelocity[0]);
     setImagesLeft();//For Two Way
  }
}
void Player::up()    {
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
}
void Player::down()  {
  if ( getY() < getWorldHeight()-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

// void Player::update(Uint32 ticks) {
//   if ( !collision ){
//     TwoWaySprite::update(ticks);
//   }
//   stop();
// }
