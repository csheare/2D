#include <sstream>
#include "poolhud.h"
#include "gamedata.h"
#include "ioMod.h"

PoolHud::PoolHud(const Player& p):
  player(p),
  renderer(RenderContext::getInstance()->getRenderer()),
  hudFrame({
            Gamedata::getInstance().getXmlInt("PoolHudPlacement/loc/x"),
            Gamedata::getInstance().getXmlInt("PoolHudPlacement/loc/y"),
            Gamedata::getInstance().getXmlInt("PoolHudPlacement/width"),
            Gamedata::getInstance().getXmlInt("PoolHudPlacement/height")
            }
  ),
  showPoolHud(true),
  io(IoMod::getInstance())
{}


void PoolHud::update(){

}

void PoolHud::draw() const {
  if(!showPoolHud) return;

  // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  // Now set the color for the hud:
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );

  //Draw the Background
  SDL_RenderFillRect( renderer, &hudFrame );

  std::stringstream strm;
  strm << "Bullet list: " << player.bulletCount();
  io.writeText(strm.str(), hudFrame.x+20,22);

  strm.clear();//clear error flags
  strm.str(""); //clear content
  strm << "Free List: " << player.freeCount();
  io.writeText(strm.str(), hudFrame.x+20,50);

  // Now set the color for the outline of the hud:
  SDL_SetRenderDrawColor( renderer,
    Gamedata::getInstance().getXmlInt("HudInfo/red"),
    Gamedata::getInstance().getXmlInt("HudInfo/green"),
    Gamedata::getInstance().getXmlInt("HudInfo/blue"),
    255/2 );
  SDL_RenderDrawRect( renderer, &hudFrame );

}
