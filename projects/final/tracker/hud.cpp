#include"hud.h"
#include "gamedata.h"
#include "renderContext.h"
#include "ioMod.h"

void Hud::draw()const{
  if(!showHud) return;

  // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  // Now set the color for the hud:
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );

  //Draw the Background
  SDL_RenderFillRect( renderer, &hudFrame );

  std::stringstream strm;
  strm << "Toggle with F1!";
  io.writeText(strm.str(), hudFrame.x+5,200);

  strm.clear();//clear error flags
  strm.str(""); //clear content

  strm << "Explode with E!";
  io.writeText(strm.str(), hudFrame.x+5,250);

  strm.clear();//clear error flags
  strm.str(""); //clear content

  strm << "Shoot with I!";
  io.writeText(strm.str(), hudFrame.x+5,300);

  strm.clear();//clear error flags
  strm.str(""); //clear content
  strm << "Move Player: ASWD";
  io.writeText(strm.str(), hudFrame.x+5,350);

  // Now set the color for the outline of the hud:
  SDL_SetRenderDrawColor( renderer,
    Gamedata::getInstance().getXmlInt("HudInfo/red"),
    Gamedata::getInstance().getXmlInt("HudInfo/green"),
    Gamedata::getInstance().getXmlInt("HudInfo/blue"),
    255/2 );
  SDL_RenderDrawRect( renderer, &hudFrame );
}

void Hud::update(){

}

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}


Hud::Hud() :
  showHud(true),
  renderer( RenderContext::getInstance()->getRenderer()),
  hudFrame({Gamedata::getInstance().getXmlInt("HudPlacement/loc/x"),
            Gamedata::getInstance().getXmlInt("HudPlacement/loc/y"),
            Gamedata::getInstance().getXmlInt("HudPlacement/width"),
            Gamedata::getInstance().getXmlInt("HudPlacement/height")
            }
  ),
  io(IoMod::getInstance())
{}
