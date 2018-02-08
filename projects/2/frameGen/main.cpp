#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "shape.h"
#include "DNA.h"


const std::string NAME = "csheare";
const int WIDTH = 600;
const int HEIGHT = 600;
const float PI = 3.14159;

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );

  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_Color bcolor = {0,0,0,0};//backbone color
  SDL_Color ccolor = {0,0,255,0};//cytosine color
  SDL_Color acolor = {0,255,0,0};//adenine color
  SDL_Color tcolor = {255,0,0,0};//thymine color
  SDL_Color gcolor = {0,255,255,0};//guanine color

  SDL_Point seg1 = {0, 0};
  SDL_Point seg2 = {200, 200};
  SDL_Point seg3 = {400, 400};

  SDL_Point center1 = {300,510};
  SDL_Point center2 = {450,100};
  SDL_Point center3 = {230,100};
  SDL_Point center4 = {480,270};
  SDL_Point center5 = {150,300};
  SDL_Point center6 = {100,200};
  SDL_Point center7 = {100,520};
  SDL_Point center8 = {400,500};

  DNA d(renderer);

  d.drawBackbone(seg1,100,0,90, bcolor,ccolor,acolor,tcolor,gcolor);
  d.drawBackbone(seg2,100,0,90, bcolor,ccolor,acolor,tcolor,gcolor);
  d.drawBackbone(seg3,100,0,90, bcolor,ccolor,acolor,tcolor,gcolor);

  d.drawCytosine(center1,40,ccolor,PI*.15);
  d.drawThymine(center2,40,tcolor,PI*2.5);
  d.drawGuanine(center3,40,gcolor,PI*44);
  d.drawAdenine(center4,40,acolor,PI/2);
  //lower
  d.drawCytosine(center5,40,ccolor,PI*88);
  d.drawThymine(center6,40,tcolor,PI/2);
  d.drawGuanine(center7,40,gcolor,PI*.6);
  d.drawAdenine(center8,40,acolor,PI);

  //Frame
  Shape top(seg1,bcolor);
  Shape bottom(seg1,bcolor);
  Shape left(seg1,bcolor);
  Shape right(seg1,bcolor);
  SDL_Point bot = {0,590};
  SDL_Point r = {590,0};
  top.drawRectangle(renderer,seg1,WIDTH,10,acolor);
  bottom.drawRectangle(renderer,bot,WIDTH,10,ccolor);
  left.drawRectangle(renderer,seg1,10,WIDTH,gcolor);
  right.drawRectangle(renderer,r,10,WIDTH,tcolor);

  std::cout << top << bottom << left << right << std::endl;

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
