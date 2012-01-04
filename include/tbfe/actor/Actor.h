class Actor; 
#ifndef Actor_L
#define Actor_L
#include "SDL/SDL.h"
#include "tbfe/misc/PropContainer.h"
#include "tbfe/Console.h"
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/SdlFunctions.h"
#include "tbfe/misc/Enums.h"
#include "tbfe/misc/StringConversion.h"
#include "tbfe/map/Map.h"
#include "tbfe/actor/Action.h"
#include "tbfe/actor/CollisionBox.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;
class Actor : public PropContainer
{
 protected:
  vector<Action> actionList_;
  Action * getAction(string);
 private:
  PositionF position_;
  Quaternion rotation_;
  Action * currentAction_;
  float speed_;
  string scriptSource_;
  string name_;
  string baseAction_;
  vector<CollisionBox> collisionMaps_;
 public:  
  Actor(int,int);
  virtual ~Actor();

  bool startAction(string);
  bool endCurrentAction();
  bool runAction();
  bool addAction(Action);
  Action getCurrentAction();
  void addCollisionBox(PositionF,PositionF);
  CollisionBox * getCollisionBox(int);
  int getNumCollisionBox();
  //Changes actorPosition relatively using direction
  int changePosition(float);
  vector<int> checkActorCollision(float,float,float);

  PositionF getPositionF();
  void setPositionF(float,float,float);

  Quaternion getRotation();
  void setRotation(Quaternion);
  void rotate(Quaternion,bool doCollisionTest=true);
  
  int getSpeed();
  void setSpeed(int);
  
  string getScriptSource();
  void setScriptSource(string);
  
  string getName();
  void setName(string);

  string getBaseAction();
  void setBaseAction(string);
};
#endif
