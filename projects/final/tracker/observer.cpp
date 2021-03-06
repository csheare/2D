#include <cmath>
#include <random>
#include <functional>
#include "observer.h"
#include "gamedata.h"
#include "subject.h"
#include "drawable.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void Observer::goLeft()  {
  setVelocityX( -std::abs(getVelocityX()) );
  setImagesLeft();
}
void Observer::goRight() {
  setVelocityX( std::fabs(getVelocityX()) );
  setImagesRight();
}
void Observer::goUp()    {setVelocityY( -fabs(getVelocityY()) ); }
void Observer::goDown()  {setVelocityY( std::fabs(getVelocityY()) );  }


Observer::Observer(const std::string& n,const Vector2f& pos,
  int w, int h) :
  TwoWaySprite(n),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(n+"/safeDistance"))
{

}

Vector2f Observer::makeVelocity(int vx, int vy) const {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  return Vector2f(newvx, newvy);
}

void Observer::update(Uint32 ticks) {
  TwoWaySprite::update(ticks);
  float x= this->getX()+this->getImage()->getWidth()/2;
  float y= this->getY()+this->getImage()->getHeight()/2;
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
