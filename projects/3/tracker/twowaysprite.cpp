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
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/Right/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/Right/startLoc/y")),
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/Right/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/Right/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(name + "/Right")),
  imagesRight(RenderContext::getInstance()->getImages(name + "/Right")),
  imagesLeft(RenderContext::getInstance()->getImages(name + "/Left")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/Right/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/Right/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s),
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
  //after so many game clock cycle
  static int direction = 1;
  static Uint32 currentTicks=0;
  currentTicks+=ticks;
  if(currentTicks >= 6000){

      direction *= -1;
      currentTicks = 0 ;

      if (direction == -1) {//set right
        setVelocityX( fabs( getVelocityX() ) );
        images = imagesRight;
      }
      if (direction == 1) {
        setVelocityX( -fabs( getVelocityX() ) );
        images = imagesLeft;
      }

  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }

  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {//set right
    setVelocityX( fabs( getVelocityX() ) );
    images = imagesRight;
  }
  if (getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
    images = imagesLeft;
    //set left image
  }

}
