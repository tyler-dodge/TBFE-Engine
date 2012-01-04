#ifndef TBFE_L
#define TBFE_L
#include "tbfe/Render.h"
#include "tbfe/Logic.h"
#include "tbfe/Camera.h"
#include "tbfe/actor/Actor.h"
#include "tbfe/actor/Npc.h"
#include "tbfe/actor/NonLiving.h"
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
  PositionI mouseMovement_;
  PositionI mousePosition_;
  PositionI mouseCenter_;
  int time_;
  void checkEvents();
  vector<EventType> eventList_;
  Timer fps_;
  Map * Current_Map;
  vector<Actor *> actors;
  bool keyControl_;
  PositionI screenDimensions_;
  float gameSpeed_;
  Camera camera_;
  Actor * Main_Player;
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
  bool addTileSet(std::string);
  EventType * getEvent(std::string);
  PositionI getMousePosition();
  PositionI getMouseCenter();
  void setMouseCenter(int,int);
  void setShowMouse(bool);
  bool getShowMouse();
  PositionF getCameraPosition();
  void addGlobalEvent(std::string,Event, int,std::string);
  int Get_Actor_Num(Actor *actorPtr);
  ~TBFE();
};
#endif
