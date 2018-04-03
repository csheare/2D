#include "player.h"

Player::Player( const std::string& name) :
  SubjectSprite(name),
  collision(false),
  initialVelocity(getVelocity())
{ }

Player::Player(const Player& s) :
  SubjectSprite(s.getName()),
  collision(s.collision),
  initialVelocity(s.getVelocity())
  { }

Player& Player::operator=(const Player& s) {
  TwoWaySprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::stop() {
  setVelocityX( 0.5*getVelocityX() );
  setVelocityY(0);
}


void Player::right() {
  if ( getX()  < worldWidth-getScaledWidth() ) {
    TwoWaySprite::setImagesRight();
    setVelocityX(initialVelocity[0]);
  }
}
void Player::left()  {
  if ( getX() > 0) {
    TwoWaySprite::setImagesLeft();
     setVelocityX(-initialVelocity[0]);
  }
}
void Player::up()    {
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
}
void Player::down()  {
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
  if ( !collision ) TwoWaySprite::update(ticks);
  stop();
}
