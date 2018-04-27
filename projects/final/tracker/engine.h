#include <vector>
#include <SDL.h>
#include "world.h"
#include "viewport.h"
#include "clock.h"
#include "collisionStrategy.h"
#include "subject.h"
#include "hud.h"
#include "poolhud.h"
#include "gamedata.h"
#include "frameGenerator.h"
#include "player.h"
#include "observer.h"


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
  World front;
  World middle;
  World back;
  Viewport& viewport;

  std::vector<Drawable*> sprites;

  int numOfSprites;
  Subject* player;
  PoolHud poolHud;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) =delete;
  void printScales() const;
  void checkForCollisions();
  void checkForDeadSprites();
};
