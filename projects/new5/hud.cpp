#include"hud.h"
#include "gamedata.h"
#include "renderContext.h"

void Hud::draw(){
  //create the window
  //set up renderer
    SDL_Rect r;
    r.x = Gamedata::getInstance().getXmlInt("HudPlacement/x");
    r.y = Gamedata::getInstance().getXmlInt("HudPlacement/y");
    r.w = Gamedata::getInstance().getXmlInt("HudPlacement/w");
    r.h = Gamedata::getInstance().getXmlInt("HudPlacement/h");

    // First set the blend mode so that alpha blending will work;
    // the default blend mode is SDL_BLENDMODE_NONE!
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Now set the color for the hud:
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );

    // Render rect
    SDL_RenderFillRect( renderer, &r );

    // Now set the color for the outline of the hud:
    SDL_SetRenderDrawColor( renderer, Gamedata::getInstance().getXmlInt("HudText/red"), Gamedata::getInstance().getXmlInt("HudText/green"), Gamedata::getInstance().getXmlInt("HudText/blue"), 255/2 );
    SDL_RenderDrawRect( renderer, &r );

    // Render the rect to the screen
    //SDL_RenderPresent(renderer);
}

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}


Hud::Hud() :
  isDis(false),
  renderer( RenderContext::getInstance()->getRenderer() ),
  window(RenderContext::getInstance()->getWindow()),
  font(TTF_OpenFont(Gamedata::getInstance().getXmlStr("font/file").c_str(),
                    Gamedata::getInstance().getXmlInt("font/size"))),
  textColor({0xff, 0, 0, 0})
{
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  textColor.r = Gamedata::getInstance().getXmlInt("font/red");
  textColor.g = Gamedata::getInstance().getXmlInt("font/green");
  textColor.b = Gamedata::getInstance().getXmlInt("font/blue");
  textColor.a = Gamedata::getInstance().getXmlInt("font/alpha");
}


void Hud::writeText(const std::string& msg, int x, int y){
  SDL_Surface* surface =
    TTF_RenderText_Solid(font, msg.c_str(),textColor);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}


bool Hud::isDisplayed() const{return isDis;}

void Hud::toggleHud(){
    isDis = !isDis;
    if(isDis){
      SDL_RenderPresent(renderer);
    }
}
