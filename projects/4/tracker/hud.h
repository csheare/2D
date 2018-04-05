

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>


//make this a meyers singleton

class Hud{

public:
static Hud& getInstance();
//~Hud();
void draw();
void toggleHud();
void writeText(const std::string& msg, int x, int y);
bool isDisplayed()const;

private:
  bool isDis;
  SDL_Renderer* renderer;
  SDL_Window* window;
  TTF_Font* font;
  SDL_Color textColor;

  Hud();

};
