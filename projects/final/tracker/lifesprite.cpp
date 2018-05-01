#include <cmath>
#include <random>
#include <functional>
#include "lifeSprite.h"
#include "gamedata.h"
#include "collisionStrategy.h"
#include "renderContext.h"

Vector2f LifeSprite::makeVelocity(int vx, int vy) const {

  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  std::cout<<newvx<<" "<<newvy <<std::endl;
  return Vector2f(newvx, newvy);
}

LifeSprite::LifeSprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Image* img):
  Drawable(n, pos, vel),
  image( img ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

LifeSprite::LifeSprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           makeVelocity(
                    Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  image( RenderContext::getInstance()->getImage(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  active(false),
  strategy( new RectangularCollisionStrategy()),
  delay(0)
{ }

LifeSprite::LifeSprite(const LifeSprite& s) :
  Drawable(s),
  image(s.image),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  active(s.active),
  strategy(s.strategy),
  delay(s.delay)
{ }

LifeSprite& LifeSprite::operator=(const LifeSprite& rhs) {
  Drawable::operator=( rhs );
  image = rhs.image;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  active = rhs.active;
  delay = rhs.delay;
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void LifeSprite::draw() const {
  if(active){
    if(getScale() < SCALE_EPSILON) return;
    image->draw(getX(), getY(), getScale());
  }
}

void LifeSprite::update(Uint32 ticks) {
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }
}

bool LifeSprite::collided(const Drawable*obj) const{
    if(strategy->execute(*this,*obj)){
      return true;
    }
    return false;
}
