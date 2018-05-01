#include "twowaysprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"


TwoWaySprite::~TwoWaySprite() { if ( explosion ) delete explosion; }


Vector2f TwoWaySprite::makeVelocity(int vx, int vy) const {

  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
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
  explosion(nullptr),
  images( RenderContext::getInstance()->getImages(name + "R")),
  imagesRight(RenderContext::getInstance()->getImages(name + "R")),
  imagesLeft(RenderContext::getInstance()->getImages(name + "L")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  alive(true)
{ }


TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  MultiSprite(s),
  explosion(s.explosion),
  images(s.images),
  imagesRight(s.imagesRight),
  imagesLeft(s.imagesLeft),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  alive(s.alive)
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
  alive = (s.alive);
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void TwoWaySprite::explode() {
  if ( !explosion ) {
    Sprite sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

void TwoWaySprite::draw() const {
  if(getScale() < SCALE_EPSILON) return;
  if ( explosion ){
    explosion->draw();
  }else{
    images[currentFrame]->draw(getX(), getY(), getScale());
  }
}
void TwoWaySprite::setImagesRight(){
  images = imagesRight;
}
void TwoWaySprite::setImagesLeft(){
  images = imagesLeft;
}



void TwoWaySprite::update(Uint32 ticks) {
  if ( explosion ) {
  explosion->update(ticks);
  if ( explosion->chunkCount() == 0 ) {
    delete explosion;
    explosion = NULL;
    this->kill();
    this->update(ticks);
  }
  return;
  }
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }

  if ( getY() > getWorldHeight()-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() > getWorldWidth()-getScaledWidth()) {
    TwoWaySprite::setVelocityX( -fabs( getVelocityX() ) );
    setImagesLeft();
  }
  if (getX() < 0) {
    TwoWaySprite::setVelocityX( fabs( getVelocityX() ) );
    setImagesRight();
  }

}
