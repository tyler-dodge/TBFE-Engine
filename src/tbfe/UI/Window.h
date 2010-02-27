#ifndef Window_L
#define Window_L
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "../misc/SdlFunctions.h"
#include "../misc/Structs.h"
#include "Element.h"
#include "ImageBox.h"
class Window
{
 private:
  Position dimensions_;
  vector<Element *> elements_;
  Position screenPosition_;
  bool showBackground_;
  bool isVisible_;
  SDL_Surface * border_;
 protected:
 public:
  Window(int,int,int,int,std::string ImageSource="");
  ~Window();
  void renderElements(SDL_Surface *);
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
