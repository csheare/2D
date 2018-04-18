#ifndef POOLHUD_H
#define POOLHUD_H

#include "gamedata.h"
#include "player.h"
#include "ioMod.h"

class PoolHud {

public:

  PoolHud(const Player& p);
  void update();
  void draw() const;
  void toggle() { showPoolHud = !showPoolHud;}

  PoolHud(const PoolHud&) = delete;//keeps compiler from generating
  PoolHud& operator=(const PoolHud&) = delete;


private:
  const Player &player;
  SDL_Renderer* renderer;
  SDL_Rect hudFrame;
  bool showPoolHud;
  const IoMod& io;

};

#endif
