#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"

Engine::~Engine() {
  for(auto d : sprites){
    delete d;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  front("front", Gamedata::getInstance().getXmlInt("front/factor") ),
  middle("middle", Gamedata::getInstance().getXmlInt("middle/factor") ),
  back("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance()),
  currentSprite(0),
  sprites({new TwoWaySprite("Eagle"), new Sprite("Boulder"), new MultiSprite("WindSpinner")}),
  numOfSprites(Gamedata::getInstance().getXmlInt("numOfSprites")),
  player(new Player("Eagle")),
  makeVideo( false )
{
  for(int i=0;i<numOfSprites;i++){
    sprites.push_back(new MultiSprite("WindSpinner"));
    sprites.push_back(new Sprite("Boulder"));
  }
  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  back.draw();
  middle.draw();
  front.draw();
  player->draw();

  for(auto d : sprites){
    d->draw();
  }

  viewport.draw(clock.getFps());
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  // static Uint32 currentTicks=0;//automatically zero!
  // currentTicks+=ticks;
  // if(currentTicks >= 5000){
  //     //switchSprite();
  //     currentTicks = 0 ;
  // }
  for(auto d : sprites){
    d->update(ticks);
  }

  player->update(ticks);
  back.update();
  middle.update();
  front.update();
  viewport.update(); // always update viewport last1

}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();

  Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
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
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
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
