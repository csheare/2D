#include "player.h"
#include <cmath>
#include "twowaysprite.h"
#include "gamedata.h"
#include "explodingSprite.h"


Player::~Player( ) {
  if (explosion) delete explosion;
 }

void Player::advanceFrame(Uint32 ticks){
  TwoWaySprite::advanceFrame(ticks);
  float speed = getVelocity().magnitude();
  frameDelay += std::max(minFrameDelay, speed);
  if(frameDelay > frameSpeed){
    incrFrame();
    frameDelay =0;
  }
}

void Player::draw() const {
  if ( explosion ) explosion->draw();
  else{
    bullets.draw();
    Uint32 x = static_cast<Uint32>(getX());
    Uint32 y = static_cast<Uint32>(getY());
    images[currentFrame]->draw(x,y);
  }
}

void Player::update(Uint32 ticks){
    if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
    }

    if ( !collision ){
        advanceFrame(ticks);
    }
    //TwoWaySprite::update(ticks);
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
      facing = RIGHT;
    }
    if(getX() > worldWidth - getScaledWidth()){
      setVelocityX(-std::abs(getVelocityX()));
      facing = LEFT;
    }

    if(delay > 0){
      delay -= ticks;
      if(getVelocityX() > 0){
        images = imagesShootRight;
        facing = RIGHT;
      }else if(getVelocityX() < 0){
        images = imagesShootLeft;
        facing = LEFT;
      }
    }
    else if(getVelocityX() > 0){
      std::cout << "Regular Right" << std::endl;
      images = imagesRight;
      facing = RIGHT;
    }
    else if(getVelocityX() < 0){
      std::cout << "Regular Left" << std::endl;
      images = imagesLeft;
      facing = LEFT;
    }
    else{
      if(facing == LEFT){
        std::cout << "Regular Left" << std::endl;
        images = imagesLeft;
      }
      else{
        std::cout << "Regular Right" << std::endl;
        images = imagesRight;
      }
    }
    stop();
}



Player::Player(const std::string& name) :
  TwoWaySprite(name),
  explosion(nullptr),
  imagesShootLeft(RenderContext::getInstance()->getImages(name + "SL")),
  imagesShootRight(RenderContext::getInstance()->getImages(name+ "SR")),
  collision(false),
  initialVelocity(getVelocity()),
  minFrameDelay(Gamedata::getInstance().getXmlFloat(name+"/minFrameDelay")),
  frameDelay(0),
  frameSpeed(Gamedata::getInstance().getXmlFloat(name+"/frameSpeed")),
  timeSinceLastImage(0),
  bulletName(Gamedata::getInstance().getXmlStr(name+"/bulletName")),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName + "/frameSpeed")),
  timeSinceLastBullet(0),
  minBulletSpeed(Gamedata::getInstance().getXmlInt(bulletName + "/minSpeed")),
  bullets(bulletName,this->getPosition(),initialVelocity),
  facing(RIGHT)
{
}

Player::Player(const Player& s) :
  TwoWaySprite(s),
  explosion(s.explosion),
  imagesShootLeft(s.imagesShootLeft),
  imagesShootRight(s.imagesShootRight),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  minFrameDelay(s.minFrameDelay),
  frameDelay(s.frameDelay),
  frameSpeed(s.frameSpeed),
  timeSinceLastImage(s.timeSinceLastImage),
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
  std::cout << "Shooting" << std::endl;
  if(getVelocityX() > 0){
    std::cout << "ShootingRight" << std::endl;
    images = imagesShootRight;
    delay = 100;
  }
  else if(getVelocityX() < 0){
    std::cout << "ShootingLeft" << std::endl;
    images = imagesShootLeft;
    delay = 100;
  }
  else if ( facing == RIGHT){
    std::cout << "ShootingRight" << std::endl;
    images = imagesShootRight;
    delay = 100;
  }
  else if( facing == LEFT){
    std::cout << "ShootingLeft" << std::endl;
    images = imagesShootLeft;
    delay = 100;
  }
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

void Player::explode() {
  if ( !explosion ) {
    Sprite
    sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

void Player::stop() {
  setVelocity( Vector2f(0,0));
}


void Player::right() {
  if ( getX()  < getWorldWidth()-getScaledWidth() ) {
    setVelocityX(initialVelocity[0]);
  }
}
void Player::left()  {
  if ( getX() > 0) {
     setVelocityX(-initialVelocity[0]);
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
// void explode(){
//   this.explode();
//     // if ( !getExplosion() ) {
//     // Sprite
//     // sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
//     // setExplosion(new ExplodingSprite(sprite));
// }

// void Player::update(Uint32 ticks) {
//   if ( !collision ){
//     TwoWaySprite::update(ticks);
//   }
//   stop();
// }
