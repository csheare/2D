#include "twowaysprite.h"
#include "gamedata.h"
#include "renderContext.h"

Vector2f TwoWaySprite::makeVelocity(int vx, int vy) const {

  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  std::cout<<"TWOWAY" <<newvx<<" "<<newvy <<std::endl;
  return Vector2f(newvx, newvy);
}


void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TwoWaySprite::TwoWaySprite( const std::string& name) :
MultiSprite(name),
  images( RenderContext::getInstance()->getImages(name)),
  imagesRight(RenderContext::getInstance()->getImages(name)),
  imagesLeft(RenderContext::getInstance()->getImages(name + "L")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  MultiSprite(s),
  images(s.images),
  imagesRight(s.imagesRight),
  imagesLeft(s.imagesLeft),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

TwoWaySprite& TwoWaySprite::operator=(const TwoWaySprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  imagesRight = (s.imagesRight);
  imagesLeft = (s.imagesLeft);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void TwoWaySprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWaySprite::update(Uint32 ticks) {
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }

  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() > worldWidth-getScaledWidth()) {//set right
    setVelocityX( -fabs( getVelocityX() ) );

  }
  if (getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }

}
