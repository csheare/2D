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

  SDL_Point seg1 = {0, 0};
  SDL_Point seg2 = {200, 200};
  SDL_Point seg3 = {400, 400};
  SDL_Point center1 = {350,150};
  SDL_Point center2 = {450,100};
  SDL_Point center3 = {200,10};
  SDL_Point center4 = {520,270};
  SDL_Point center5 = {150,300};
  SDL_Point center6 = {100,200};
  SDL_Point center7 = {200,520};
  SDL_Point center8 = {400,500};
  SDL_Color bcolor = {0,0,0,0};//backbone color
  SDL_Color ccolor = {0,0,255,0};//cytosine color
  SDL_Color acolor = {0,255,0,0};//adenine color
  SDL_Color tcolor = {255,0,0,0};//thymine color
  SDL_Color gcolor = {0,255,255,0};//guanine color
  Draw d(renderer);
  d.drawDNA(seg1,100,0,90, bcolor,ccolor,acolor,tcolor,gcolor);
  d.drawDNA(seg2,100,0,90, bcolor,ccolor,acolor,tcolor,gcolor);
  d.drawDNA(seg3,100,0,90, bcolor,ccolor,acolor,tcolor,gcolor);
  d.drawCytosine(center1,65,55,ccolor);
  d.drawThymine(center2,45,35,tcolor);
  d.drawGuanine(center3,50,50,gcolor);
  d.drawAdenine(center4,50,50,acolor);
  //lower
  d.drawCytosine(center5,65,55,ccolor);
  d.drawThymine(center6,45,35,tcolor);
  d.drawGuanine(center7,50,50,gcolor);
  d.drawAdenine(center8,50,50,acolor);


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
