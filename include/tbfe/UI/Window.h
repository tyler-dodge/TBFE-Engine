#ifndef Window_L
#define Window_L
#include <boost/python.hpp>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "tbfe/misc/SdlFunctions.h"
#include "tbfe/misc/Structs.h"
#include "tbfe/UI/Element.h"
class Window
{
 private:
  PositionI dimensions_;
  vector<Element *> elements_;
  PositionI screenPosition_;
  bool showBackground_;
  bool isVisible_;
  SDL_Surface * background_;
  SDL_Surface * image_;
 protected:
 public:
  Window(int,int,int,int,std::string ImageSource="");
  ~Window();
  SDL_Surface * renderElements();
  void addElement(Element *);
  Element * getElement(std::string);
  PositionI getDimensions();
  void setDimensions(int,int);
  
  PositionI getScreenPosition();
  void setScreenPosition(int,int);

  bool getVisibility();
  void setVisibility(bool);

  bool getShowBackground();
  void setShowBackground(bool);
};
#endif
