#include <cmath>
#include <random>
#include <functional>
#include "observer.h"
#include "gamedata.h"
#include "renderContext.h"
#include "subject.h"
#include "drawable.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void Observer::goLeft()  {getDrawable()->setVelocityX( -std::abs(getDrawable()->getVelocityX()) );}
void Observer::goRight() {getDrawable()->setVelocityX( std::fabs(getDrawable()->getVelocityX()) );}
void Observer::goUp()    { getDrawable()->setVelocityY( -fabs(getDrawable()->getVelocityY()) ); }
void Observer::goDown()  { getDrawable()->setVelocityY( std::fabs(getDrawable()->getVelocityY()) );  }


Observer::Observer(Drawable *draw,const Vector2f& pos,
  int w, int h) :
  Drawable(draw->getName(),draw->getPosition(),draw->getVelocity()),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(getDrawable()->getName()+"/safeDistance")),
  drawable(draw)
{}

void Observer::update(Uint32 ticks) {
  getDrawable()->update(ticks);
  float x= getDrawable()->getX()+getDrawable()->getImage()->getWidth()/2;
  float y= getDrawable()->getY()+getDrawable()->getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) currentMode = EVADE;
  }
  else if  ( currentMode == EVADE ) {
    if(distanceToEnemy > safeDistance) {
      currentMode=NORMAL;
    }
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }
}

void Observer::draw() const{
  getDrawable()->draw();
}


Vector2f Observer::makeVelocity(int vx, int vy) const {

  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  return Vector2f(newvx, newvy);
}

Drawable *Observer::getDrawable() const{
  return drawable;
}

int Observer::getScaledWidth() const{
  return getDrawable()->getScaledWidth();
}
int Observer::getScaledHeight() const{
  return getDrawable()->getScaledHeight();
}
const SDL_Surface* Observer::getSurface() const{
  return getDrawable()->getSurface();
}
const Image* Observer::getImage() const{
  return getDrawable()->getImage();
}
void Observer::setVelocityX(float vx){
  return getDrawable()->setVelocityX(vx);
}
int Observer::getWorldWidth() const{
  return getDrawable()->getWorldWidth();
}
int Observer::getWorldHeight() const{
  return getDrawable()->getWorldHeight();
}
