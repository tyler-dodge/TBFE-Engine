#ifndef TBFE_Logic_L
#define TBFE_Logic_L
#include "SDL/SDL.h"
#include "actor/Actor.h"
#include "Base.h"
class TBFE_Logic
{
 private:
  SDL_Event event_;
  bool keysDown_[316];
 public:
  SDL_Event getEvent();
  bool pollEvent();
  bool checkKeyDown(int);
  void setKeyDown(int,bool);
  void playerMovement();
  int contextAction();
  int checkTalker();
  char textInput(int,bool);
  //KeyUps
  TBFE_Logic();
  ~TBFE_Logic();
};
#endif
