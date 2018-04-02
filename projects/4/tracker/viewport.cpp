#include <sstream>
#include "viewport.h"
#include "ioMod.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() :
  gdata(Gamedata::getInstance()),
  position(0, 0),
  worldWidth(gdata.getXmlInt("world/width")),
  worldHeight(gdata.getXmlInt("world/height")),
  viewWidth(gdata.getXmlInt("view/width")),
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL)
{}

void Viewport::setObjectToTrack(const Drawable *obj) {
  objectToTrack = obj;
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw(int fps) const {
  SDL_Color c = {255,123,5,0};
  IoMod::getInstance().
    writeText("Tracking: "+objectToTrack->getName(), 30, 30);
  IoMod::getInstance().
    writeText("Name: Courtney ", 0, 450,c);
    std::stringstream ss;
    std::string s;
    ss <<fps;
    ss >> s;
  IoMod::getInstance().
      writeText("FPS:" + s, 30, 100);
}

void Viewport::update() {
  const float x = objectToTrack->getX();
  const float y = objectToTrack->getY();

  position[0] = (x + objWidth/2) - viewWidth/2;
  position[1] = (y + objHeight/2) - viewHeight/2;
  if (position[0] < 0) position[0] = 0;
  if (position[1] < 0) position[1] = 0;
  if (position[0] > (worldWidth - viewWidth)) {
    position[0] = worldWidth-viewWidth;
  }
  if (position[1] > (worldHeight - viewHeight)) {
    position[1] = worldHeight-viewHeight;
  }
}
