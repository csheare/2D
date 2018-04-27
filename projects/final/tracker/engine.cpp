#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "observer.h"


#include "engine.h"

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
  player(new Subject("Eagle")),
  poolHud(*(dynamic_cast<Player*>(player))),
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
      sprites.push_back(new Observer("GreenBird",pos, w, h));
      sprites[i]->setVelocity(static_cast<Observer*>(sprites[i])->makeVelocity(sprites[i]->getVelocityX(), sprites[i]->getVelocityY()));
      //std::cout << "Sprite Velocity (x,y): " << sprites[i]->getVelocityX() << " , " << sprites[i]->getVelocityY() <<std::endl;

      player->attach(static_cast<Observer*>(sprites[i]));
  }

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  back.draw();
  middle.draw();
  front.draw();
  hud.draw();
  poolHud.draw();

  player->draw();
  for(Drawable* sprite : sprites){
    static_cast<Observer*>(sprite)->draw();
  }

  //strategies[currentStrategy]->draw();

  //viewport.draw(clock.getFps());
  SDL_RenderPresent(renderer);
}
void Engine::checkForCollisions() {
  auto it = sprites.begin();
  while ( it != sprites.end() ) {
    if ( player->getBullets().collided(*it)){//trategies[currentStrategy]->execute(*player, **it ) ){
      std::cout << "REMOVING SPRITE\n" << std::endl;
      Observer* doa = static_cast<Observer*>(*it);
      doa->explode();
      doa->update(clock.getElapsedTicks());
    }
        ++it;

  }
}

void Engine::checkForDeadSprites(){
  auto ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
      if((static_cast<TwoWaySprite*>(*ptr)->isAlive()) == false){
        ptr = sprites.erase(ptr);


      }else{
            ptr++;
      }
  }
}

void Engine::update(Uint32 ticks) {
  back.update();
  middle.update();
  front.update();

  for(Drawable* s : sprites){
    static_cast<Observer*>(s)->update(ticks);
  }

  checkForDeadSprites();
  checkForCollisions();

  player->update(ticks);

  viewport.update(); // always update viewport last1
  //i never updated the hud
}



bool Engine::play() {
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
        if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
          return true;
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          hud.toggle();
        }
        if(keystate[SDL_SCANCODE_I]){
            player->shoot();
        }
        if ( keystate[SDL_SCANCODE_E] ) {
          std::cout << "DIE" << std::endl;
            player->explode();
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
  return false;
}
