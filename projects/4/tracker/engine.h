#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "world.h"
#include "viewport.h"
#include "clock.h"
#include "collisionStrategy.h"
#include "subjectSprite.h"
#include "hud.h"

class Engine {
public:
  Engine ();
  ~Engine ();

  void play();
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
  std::vector<SmartSprite*> sprites;
  //std::vector<Drawable*> sprites;
  int numOfSprites;
  SubjectSprite * player;
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
};
