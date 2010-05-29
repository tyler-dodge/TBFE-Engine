#ifndef Window_L
#define Window_L
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "../misc/SdlFunctions.h"
#include "../misc/Structs.h"
#include "Element.h"
class Window
{
 private:
  Position dimensions_;
  vector<Element *> elements_;
  Position screenPosition_;
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
  Position getDimensions();
  void setDimensions(int,int);
  
  Position getScreenPosition();
  void setScreenPosition(int,int);

  bool getVisibility();
  void setVisibility(bool);

  bool getShowBackground();
  void setShowBackground(bool);
};
#endif
