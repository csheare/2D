#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "smartsprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"
#include "subjectSprite.h"

Engine::~Engine() {
  delete player;
  for ( Drawable* sprite : sprites ) {
    delete sprite;
  }
  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  hud(Hud::getInstance()),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  front("front", Gamedata::getInstance().getXmlInt("front/factor") ),
  middle("middle", Gamedata::getInstance().getXmlInt("middle/factor") ),
  back("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance()),
  sprites(),
  numOfSprites(Gamedata::getInstance().getXmlInt("numOfSprites")),
  player(new SubjectSprite("Eagle")),
  strategies(),
  currentStrategy(0),
  collision(false),
  makeVideo(false)
{
  sprites.reserve(numOfSprites);
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  for(int i=0;i<numOfSprites;i++){
    //std::cout << "Adding Sprite!" <<std::endl;
    sprites.push_back(new SmartSprite("GreenBird",pos, w, h));
    sprites[i]->setVelocity(sprites[i]->makeVelocity(sprites[i]->getVelocityX(), sprites[i]->getVelocityY()));
    player->attach( sprites[i] );
  hud.draw();
  hud.writeText(Gamedata::getInstance().getXmlStr("HudText/Line1"),Gamedata::getInstance().getXmlInt("HudPlacement/x"),Gamedata::getInstance().getXmlInt("HudPlacement/y")-30);
  hud.writeText(Gamedata::getInstance().getXmlStr("HudText/Line2"),Gamedata::getInstance().getXmlInt("HudPlacement/x"),Gamedata::getInstance().getXmlInt("HudPlacement/y")-5);
  }

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
  hud.toggleHud();
}

void Engine::draw() const {
  back.draw();
  middle.draw();
  front.draw();
  IoMod::getInstance().writeText("Press m to change strategy", 500, 60);
  for(const Drawable* sprite : sprites){
    sprite->draw();
  }
  std::stringstream strm;
  strm << sprites.size() << " Smart Sprites Remaining";
  IoMod::getInstance().writeText(strm.str(), 30, 60);
  strategies[currentStrategy]->draw();
  if ( collision ) {
    IoMod::getInstance().writeText("Oops: Collision", 500, 90);
  }
  player->draw();
  if(hud.isDisplayed()){
    hud.draw();
    hud.writeText(Gamedata::getInstance().getXmlStr("HudText/Line1"),Gamedata::getInstance().getXmlInt("HudPlacement/x"),Gamedata::getInstance().getXmlInt("HudPlacement/y")+30);
    hud.writeText(Gamedata::getInstance().getXmlStr("HudText/Line2"),Gamedata::getInstance().getXmlInt("HudPlacement/x"),Gamedata::getInstance().getXmlInt("HudPlacement/y")+5);
  }
  viewport.draw(clock.getFps());
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  auto it = sprites.begin();
  while ( it != sprites.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      SmartSprite* doa = *it;
      //player->detach(doa);
      //it = sprites.erase(it);
      //delete doa;
      doa->update(clock.getElapsedTicks());
    }//else{
          ++it;


  }
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();
  player->update(ticks);
  for(SmartSprite* s : sprites){
    s->update(ticks);
  }

  back.update();
  middle.update();
  front.update();
  viewport.update(); // always update viewport last1

}



void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          hud.toggleHud();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        static_cast<Player*>(player)->left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        static_cast<Player*>(player)->right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        static_cast<Player*>(player)->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        static_cast<Player*>(player)->down();
      }

      update(ticks);
      draw();


      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
