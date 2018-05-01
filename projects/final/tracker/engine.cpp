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

#include "multisprite.h"
#include "twowaysprite.h"
#include "observer.h"



#include "engine.h"

Engine::~Engine() {
  delete player;
  for ( Drawable* sprite : sprites ) {
    delete sprite;
  }
  delete healthBar;
  delete lifeSprite;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  hud(Hud::getInstance()),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  menuEngine(),
  front("front", Gamedata::getInstance().getXmlInt("front/factor") ),
  middle("middle", Gamedata::getInstance().getXmlInt("middle/factor") ),
  back("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance()),
  healthBar(new HealthBar("HealthBar")),
  sprites(),
  numOfSprites(Gamedata::getInstance().getXmlInt("numOfSprites")),
  player(new Subject("Eagle")),
  lifeSprite(new LifeSprite("Heart")),
  poolHud(*(dynamic_cast<Player*>(player))),
  strategies(),
  currentStrategy(0),
  collision(false),
  sound(),
  makeVideo(false)
{
  sprites.reserve(numOfSprites);
  loadSprites();
  lifeSprite->setDelay(100);//starts delay clock
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
  if(!player->isAlive()){
    io.writeText("You Lose! Press R to Restart the game", 250, 200);
    lifeSprite->stop();
    lifeSprite->setDelay(-1);
    //clock.pause();
  }

  if(lifeSprite->isActive()){
    lifeSprite->draw();
  }


  for(Drawable* sprite : sprites){
    static_cast<Observer*>(sprite)->draw();
  }

  std::stringstream strm;
   if ( sprites.size() == 0 ) {
     io.writeText("You Win! Press R to Restart the game", 250, 200);
     clock.pause();
   }

  healthBar->draw();


  if ( healthBar->getCurrentLength() == 0 ) {
    player->explode();
    player->kill();
  }

  SDL_RenderPresent(renderer);
}
void Engine::checkForCollisions() {
  auto it = sprites.begin();
  while ( it != sprites.end() ) {
    if ( player->getBullets().collided(*it)){
      //std::cout << "REMOVING SPRITE\n" << std::endl;
      Observer* doa = static_cast<Observer*>(*it);
      doa->explode();
      doa->update(clock.getElapsedTicks());
    }
        ++it;
  }
  if(lifeSprite->isActive() && lifeSprite->collided(player)){
     lifeSprite->toggle();
     healthBar->incrementHealthBar(10);
     lifeSprite->setDelay(100);
  }
}

void Engine::checkForDeadSprites(){
  auto ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
      if((static_cast<TwoWaySprite*>(*ptr)->isAlive()) == false){
        Drawable * doa = *ptr;
        ptr = sprites.erase(ptr);
        delete doa;
      }else{
            ptr++;
      }
  }
}

void Engine::killAllSprites(){
  //delete odd
  for ( Drawable* sprite : sprites ) {
    dynamic_cast<TwoWaySprite*>(sprite)->kill();
  }
}

void Engine::loadSprites(){
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();

  for(int i=0;i<numOfSprites;i++){
      sprites.push_back(new Observer("GreenBird",pos, w, h));
      sprites[i]->setVelocity(static_cast<Observer*>(sprites[i])->makeVelocity(sprites[i]->getVelocityX(), sprites[i]->getVelocityY()));
      player->attach(static_cast<Observer*>(sprites[i]));
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

  if(lifeSprite->isActive()){
      lifeSprite->update(ticks);
  }else{
    lifeSprite->decrementDelay();
    if(lifeSprite->getDelay() == 0){
      lifeSprite->toggle();
    }
  }
  healthBar->update(ticks);

  viewport.update(); // always update viewport last1
}



bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
  throw (std::string("Could not init SDL: ") + SDL_GetError());
}

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        } if ( keystate[SDL_SCANCODE_SPACE] ) {
            sound.toggleMusic();
        }
        if ( keystate[SDL_SCANCODE_M] || keystate[SDL_SCANCODE_O] ) {
          clock.pause();
          menuEngine.play(0);
          if(menuEngine.spritesOptionChosen()){//chose starts
              numOfSprites = menuEngine.getNumSprites();
              killAllSprites();
              loadSprites();
          }if(menuEngine.getDifficulty() != (-1)){
            std::cout << menuEngine.getDifficulty() << std::endl;
            if(menuEngine.getDifficulty() == 1){
              healthBar->reset();
              numOfSprites = 1;
              killAllSprites();
              loadSprites();
            }
            if(menuEngine.getDifficulty() == 2){
              healthBar->reset();
              numOfSprites = 10;
              killAllSprites();
              loadSprites();
            }if(menuEngine.getDifficulty() == 3){//must be 3
              healthBar->reset();
              numOfSprites = 100;
              killAllSprites();
              loadSprites();
            }
            menuEngine.setDifficulty(-1);
          }if(menuEngine.godModeOn()){
            healthBar->incrementHealthBar(10000);
          }
          clock.unpause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          static_cast<HealthBar*>(healthBar)->incrementHealthBar(10);
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
