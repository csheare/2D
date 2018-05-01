#include <vector>
#include <SDL.h>
#include "menu.h"

class MenuEngine {
public:
  MenuEngine ();
  ~MenuEngine ();
  void play(int currentMenu);
  int getOptionChoice() const { return optionChoice; }
  bool spritesOptionChosen();
  int getDifficulty(){ return difficulty;}
  void setDifficulty(int x){ difficulty = x;}
  int getNumSprites() const { return numSprites; }
  void setCurrentMenu(int x){ currentMenu = x;}
  int getCurrentMenu(){ return currentMenu;}
  void toggleGodMode(){ isGod = !isGod;}
  bool godModeOn(){return isGod;}


private:
  Clock& clock;
  SDL_Renderer * const renderer;
  Menu menu;
  Menu diffMenu;
  int optionChoice;
  bool spritesOption;
  int numSprites;
  int difficulty;
  int currentMenu;
  bool isGod;

  void draw() const;
  void update(Uint32);

  MenuEngine(const MenuEngine&);
  MenuEngine& operator=(const MenuEngine&);
};
