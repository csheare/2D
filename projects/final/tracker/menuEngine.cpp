#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include "sprite.h"
#include "gamedata.h"
#include "menuEngine.h"
#include "renderContext.h"

MenuEngine::~MenuEngine() { }

MenuEngine::MenuEngine() :
  clock( Clock::getInstance() ),
  renderer( RenderContext::getInstance()->getRenderer() ),
  menu( renderer, "0" ),
  diffMenu(renderer, "1"),
  optionChoice(-1),
  spritesOption(false),
  numSprites(Gamedata::getInstance().getXmlInt("numOfSprites")),
  difficulty(-1),
  currentMenu(0),
  isGod(false)
{
}

void MenuEngine::draw() const {
  if(currentMenu == 0){
    menu.draw();
  }else{
    diffMenu.draw();
  }

  SDL_RenderPresent(renderer);
}

bool MenuEngine::spritesOptionChosen() {
  if ( spritesOption ) {
    spritesOption = false;
    return true;
  }
  return false;
}

void MenuEngine::update(Uint32) {
}

void MenuEngine::play(int m) {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;

    while ( !done ) {
      // The next loop polls for events, guarding against key bounce:
      if(m == 0){
        while ( SDL_PollEvent(&event) ) {
          keystate = SDL_GetKeyboardState(NULL);
          if (event.type ==  SDL_QUIT) { done = true; break; }
          if(event.type == SDL_KEYDOWN) {
            if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
              done = true;
              break;
            }
            if (keystate[SDL_SCANCODE_DOWN] ) menu.incrIcon();
            if (keystate[SDL_SCANCODE_UP] ) menu.decrIcon();
            if (keystate[SDL_SCANCODE_RETURN] ) {
              menu.lightOn();
              optionChoice = menu.getOptionNo();
              if ( optionChoice == 0 ) done = true;
              if ( optionChoice == 1 ) {
                spritesOption = true;
                numSprites = menu.getNumSprites();
                //std::cout << "No is: " << numStars << std::endl;
              }
              if(optionChoice == 2){
                m=1;
                setCurrentMenu(1);
              }if(optionChoice == 3){
                toggleGodMode();
              }
            }
          }
          if(event.type == SDL_KEYUP) {
            menu.lightOff();
          }
        }
        // In this section of the event loop we allow key bounce:
        draw();
      }else{//current Menu is Sub Menu for Difficult
      // The next loop polls for events, guarding against key bounce:
        while ( SDL_PollEvent(&event) ) {
          keystate = SDL_GetKeyboardState(NULL);
          if (event.type ==  SDL_QUIT) { done = true; break; }
          if(event.type == SDL_KEYDOWN) {
            if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
              done = true;
              m = 0;
              setCurrentMenu(0);
              break;
            }
            if (keystate[SDL_SCANCODE_DOWN] ) diffMenu.incrIcon();
            if (keystate[SDL_SCANCODE_UP] ) diffMenu.decrIcon();
            if (keystate[SDL_SCANCODE_RETURN] ) {
              diffMenu.lightOn();
              optionChoice = diffMenu.getOptionNo();
              if ( optionChoice == 0 ) difficulty = 1;
              if(optionChoice == 1) difficulty = 2;
              if(optionChoice == 2) difficulty = 3;
            }
          }
          if(event.type == SDL_KEYUP) {
            diffMenu.lightOff();
          }
        }
        // In this section of the event loop we allow key bounce:
        draw();
      }
  }
}
