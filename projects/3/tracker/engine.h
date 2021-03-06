#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "world.h"
#include "viewport.h"
#include "clock.h"

class Engine {
public:
  Engine ();
  ~Engine ();

  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World front;
  World middle;
  World back;
  Viewport& viewport;
  int currentSprite;
  std::vector<Drawable*> sprites;
  int numOfSprites;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) =delete;
  void printScales() const;
  void checkForCollisions();
};
