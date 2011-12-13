#ifndef TBFE_L
#define TBFE_L
#include <boost/python.hpp>
#include "tbfe/Base.h"
#include "tbfe/Render.h"
#include "tbfe/Logic.h"
#include "tbfe/actor/Actor.h"
#include "tbfe/actor/Npc.h"
#include "tbfe/actor/NonLiving.h"
#include "tbfe/UI/Window.h"
#include "tbfe/UI/WindowCreate.h"
#include "tbfe/actor/ActorCreate.h"
#include <sstream>
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/StringConversion.h"
#include <vector>
using namespace std;

//functions
class TBFE
{
 private:
  float frame_;  
  bool mouseDown_;
  bool showMouse_;
  bool quit_;
  Timer frameRate_;
  Position mouseMovement_;
  Position mousePosition_;
  Position mouseCenter_;
  int time_;
  void checkEvents();
  vector<EventType> eventList_;
  Timer fps_;
 protected:
  TBFE_Render renderWindow_;
  TBFE_Logic logic_;
 public:
  bool createFile(string);
  TBFE(int dimensionX,int dimensionY);
  void changeMap(std::string);
  void initMap();
  Direction runEngine();
  void addActor(Actor*);
  bool removeActor(Actor *);
  void addWindow(Window *);
  bool addTileSet(std::string);
  void addEvent(std::string,Element *, Window *,std::string,Event);
  EventType * getEvent(std::string);
  Position getMousePosition();
  Position getMouseCenter();
  void setMouseCenter(int,int);
  void setShowMouse(bool);
  bool getShowMouse();
  PositionF getCameraPosition();
  void addGlobalEvent(std::string,Event, int,std::string);
  ~TBFE();
};
#endif
