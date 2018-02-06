#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "draw.h"

const std::string NAME = "csheare";
const int WIDTH = 600;
const int HEIGHT = 600;

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );

  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
  //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  SDL_Point center = {0, 0};
  SDL_Point center2 = {200, 200};
  SDL_Point center3 = {400, 400};
  SDL_Color color = {255,0,0,0};
  SDL_Color color2 = {0,0,255,0};
  Draw d(renderer);
  // d.drawDNA(center,100,0,90, color);
  // d.drawDNA(center2,100,0,90, color2);
  // d.drawDNA(center3,100,0,90, color);
  d.drawPentagon(center2,50,50,color);


  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
