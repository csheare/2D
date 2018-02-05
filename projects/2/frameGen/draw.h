#include <string>
#include <SDL.h>

class Draw{
public:
  Draw(SDL_Renderer* r);
  void drawCircle(SDL_Point center, int radius, SDL_Color color);
  void drawRect(SDL_Point center, int width, int height, SDL_Color color);
  void drawBackbone(SDL_Point center, int radius,float startAngle, float endAngle, SDL_Color color);
  void drawEllipse(SDL_Point center, int a, int b ,SDL_Color color);
private:
  SDL_Renderer* renderer;
};
