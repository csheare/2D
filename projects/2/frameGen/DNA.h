#include <string>
#include <SDL.h>

class DNA{
public:
  DNA(SDL_Renderer* r);

  void drawBackbone(SDL_Point center, int radius,float startAngle, float endAngle, SDL_Color color,SDL_Color cyt,SDL_Color ad,SDL_Color thy,SDL_Color guan);
  void drawPurine(SDL_Point center,int radius,SDL_Color color,int rotation);
  void drawPyrimidine(SDL_Point center,int radius,SDL_Color color,int rotation);
  void drawCytosine(SDL_Point center,int radius,SDL_Color color,int rotation);
  void drawThymine(SDL_Point center,int radius,SDL_Color color,int rotation);
  void drawAdenine(SDL_Point center,int radius,SDL_Color color,int rotation);
  void drawGuanine(SDL_Point center,int radius,SDL_Color color,int rotation);

private:
  SDL_Renderer* renderer;
};
