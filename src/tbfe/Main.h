#ifndef TBFE_L
#include "Base.h"
#include "Render.h"
#include "Logic.h"
#include "actor/Actor.h"
#include "actor/Npc.h"
#include "actor/NonLiving.h"
#include "UI/Window.h"
#include "UI/WindowCreate.h"
#include "actor/ActorCreate.h"
#include <sstream>
#include "misc/Structs.h"
#include "misc/StringConversion.h"
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
  TBFE();
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
