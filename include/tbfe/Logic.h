#ifndef TBFE_Logic_L
#define TBFE_Logic_L
#include <boost/python.hpp>
#include "SDL/SDL.h"
#include "tbfe/actor/Actor.h"
#include "tbfe/Base.h"
class TBFE_Logic
{
 private:
  SDL_Event event_;
  bool keysDown_[316];
  bool newEvent_;
 public:
  SDL_Event getEvent();
  bool pollEvent();
  bool isEventNew();
  bool checkKeyDown(int);
  void setKeyDown(int,bool);
  void playerMovement();
  char textInput(int,bool);
  //KeyUps
  TBFE_Logic();
  ~TBFE_Logic();
};
#endif