#include <vector>
#include <SDL.h>
#include "world.h"
#include "viewport.h"
#include "collisionStrategy.h"
#include "subject.h"
#include "hud.h"
#include "poolhud.h"
#include "frameGenerator.h"
#include "player.h"
#include "observer.h"
#include "menuEngine.h"
#include "ioMod.h"
#include "healthBar.h"
#include "lifeSprite.h"
#include "sound.h"


class Engine {
public:
  Engine ();
  ~Engine ();

  bool play();
  void switchSprite();

private:
  const RenderContext* rc;

  const IoMod& io;
  Hud& hud;
  Clock& clock;

  SDL_Renderer * const renderer;
  MenuEngine menuEngine;
  World front;
  World middle;
  World back;
  Viewport& viewport;
  HealthBar* healthBar;

  std::vector<Drawable*> sprites;

  int numOfSprites;
  Subject* player;
  LifeSprite * lifeSprite;
  PoolHud poolHud;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;
  SDLSound sound;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) =delete;
  void printScales() const;
  void checkForCollisions();
  void checkForDeadSprites();
  void killAllSprites();
  void loadSprites();
};
