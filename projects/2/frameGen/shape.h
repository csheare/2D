#include <stdlib.h>
#include <SDL.h>
#include<vector>

class Shape{
public:
  Shape(SDL_Point c,SDL_Color col): center(c), color(col){};
  void setPentagon(int radius);
  void setHexagon(int radius);
  void drawRectangle(SDL_Renderer* renderer,SDL_Point center,int width, int height, SDL_Color color);
  void drawCircle(SDL_Renderer * renderer,SDL_Point center,int radius, SDL_Color color);
  void drawDouble(SDL_Renderer *renderer,float rotation,Shape s);
  void draw(SDL_Renderer *renderer,float rotation);
  std::vector<SDL_Point> getPoints();
  void addPoints(std::vector<SDL_Point> vec);
  void rotatePoints(int rotation);
  int getX() const{ return center.x;}
  int getY() const{ return center.y;}

private:
  SDL_Point center;
  SDL_Color color;
  std::vector<SDL_Point> points;
};
std::ostream& operator<<(std::ostream & out, const Shape& s);
