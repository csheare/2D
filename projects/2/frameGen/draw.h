#include <string>
#include <SDL.h>

class Draw{
public:
  Draw(SDL_Renderer* r);
  void drawCircle(SDL_Point center, int radius, SDL_Color color);
  void drawRect(SDL_Point center, int width, int height, SDL_Color color);
  void drawDNA(SDL_Point center, int radius,float startAngle, float endAngle, SDL_Color color,SDL_Color cyt,SDL_Color ad,SDL_Color thy,SDL_Color guan);
  void drawHexagon(SDL_Point tip,int width, int height,SDL_Color color);
  void drawPurine(SDL_Point tip,int width,int height,SDL_Color color);
  void drawPyrimidine(SDL_Point center,int width,int height,SDL_Color color);
  void drawCytosine(SDL_Point tip,int width,int height,SDL_Color color);
  void drawThymine(SDL_Point tip,int width,int height,SDL_Color color);
  void drawAdenine(SDL_Point tip,int width,int height,SDL_Color color);
  void drawGuanine(SDL_Point tip,int width,int height,SDL_Color color);

  //Adenine
  //Guanine
  //Cytosine
  //Thymine
private:
  SDL_Renderer* renderer;
};
