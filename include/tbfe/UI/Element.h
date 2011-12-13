#ifndef Element_L
#define Element_L
#include <boost/python.hpp>
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/SdlFunctions.h"
#include "tbfe/Base.h"

class Element
{
 private:
  SDL_Surface * background_;
  Position currentPosition_;
  Position dimensions_;
  std::string name_;
  std::string special_;
  bool isVisible_;
  vector<Property> propertyList_;
 protected:
  SDL_Surface * intermediary_;
 public:
  SDL_Surface * getBackground();
  void setBackground(string);

  Position getPosition();
  void setPosition(int,int);

  Position getDimensions();
  void setDimensions(int,int);

  string getName();
  void setName(string);

  string getProperty(string);
  void setProperty(string,string);
  bool getVisibility();
  void setVisibility(bool);
  void drawBorders();
  virtual SDL_Surface * renderElement()=0;
  virtual void reload()=0;
  Element(int,int);
  virtual ~Element();
};
#endif
