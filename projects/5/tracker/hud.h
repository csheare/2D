#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <sstream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

class IoMod;


//make this a meyers singleton

class Hud{

public:
static Hud& getInstance();
//~Hud();
void update();
void draw() const;
void toggle() {showHud = !showHud;}


private:
  bool showHud;
  SDL_Renderer* renderer;
  SDL_Rect hudFrame;
  IoMod& io;
  Hud();

};

#endif
