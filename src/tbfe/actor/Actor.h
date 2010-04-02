class Actor;
#ifndef Actor_L
#define Actor_L
#include "SDL/SDL.h"
#include "../Console.h"
#include "../misc/Structs.h"
#include "../misc/SdlFunctions.h"
#include "../misc/Enums.h"
#include "../misc/StringConversion.h"
#include "../map/Map.h"
#include "../Base.h"
#include "Action.h"
#include "Animation.h"
#include "CollisionBox.h"
#include "Inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
class Actor
{
 protected:
  vector<Action> actionList_;
  vector<Property> propertyList_;
  Action * getAction(string);
  std::string conversation_;
 private:
  PositionF position_;
  PositionF rotation_;
  int angle_;
  Action * currentAction_;
  float speed_;
  string scriptSource_;
  string name_;
  string baseAction_;
  bool isWalking_;
  bool isMobile_;
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
  string getProperty(string);
  void setProperty(string,string);
  int changePosition(float,bool);

  int checkActorCollision(float,float,float);

  Position getPosition();
  void setPosition(int,int,int Z=0);

  PositionF getPositionF();
  void setPositionF(float,float,float);

  PositionF getRotationF();
  void setRotationF(float,float,float);
  virtual string getConversation(bool)=0;
  void setConversation(string);
  
  int getSpeed();
  void setSpeed(int);
  
  string getScriptSource();
  void setScriptSource(string);
  
  string getName();
  void setName(string);

  string getBaseAction();
  void setBaseAction(string);

  bool getWalking();
  void setWalking(bool);

  bool getMobile();
  void setMobile(bool);

  Position getDirOffset();

};
#endif
