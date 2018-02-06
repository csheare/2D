#include <string>
#include <SDL.h>

class Draw{
public:
  Draw(SDL_Renderer* r);
  void drawCircle(SDL_Point center, int radius, SDL_Color color);
  void drawRect(SDL_Point center, int width, int height, SDL_Color color);
  void drawDNA(SDL_Point center, int radius,float startAngle, float endAngle, SDL_Color color);
  void drawPentagon(SDL_Point tip,int width, int height,SDL_Color color);
  void drawHexagon(SDL_Point tip,SDL_Color color);
  void drawTriangle(SDL_Point center,SDL_Color color);
  //Adenine
  //Guanine
  //Cytosine
  //Thymine
private:
  SDL_Renderer* renderer;
};
