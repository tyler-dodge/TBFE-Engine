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
  string collisionSource_;
  Action * getAction(string);
  std::string conversation_;
 private:
  PositionD position_;
  PositionD rotation_;
  int angle_;
  Action * currentAction_;
  SDL_Surface * collisionMap_;
  float speed_;
  string scriptSource_;
  string name_;
  string baseAction_;
  bool isWalking_;
  bool isMobile_;
  Position collisionDimensions_;
 public:  
  Actor(int,int);
  virtual ~Actor();

  bool startAction(string);
  bool endCurrentAction();
  bool runAction();
  bool addAction(Action);
  Action getCurrentAction();
  
  //Changes actorPosition relatively using direction
  string getProperty(string);
  void setProperty(string,string);
  int changePosition(int,bool);
  void changeScreen(int,int);

  SDL_Rect getCollisionRect(); 
  SDL_Surface * getCollisionMap();
  void setCollisionMap(string);
  void loadCollisionMap(string);
  bool advancedCollision(SDL_Surface *,SDL_Rect,Position);  
  int checkActorCollision(bool,int OffsetX=0,int OffsetY=0);

  Position getPosition();
  void setPosition(int,int,int Z=0);

  PositionD getPositionD();
  void setPositionD(double,double,double);

  PositionD getRotationD();
  void setRotationD(double,double,double);

  int getAngle();
  void setAngle(int);

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

  Position getCollisionDimensions();
  void setCollisionDimensions(int,int,int);

  bool getWalking();
  void setWalking(bool);

  bool getMobile();
  void setMobile(bool);

  Position getDirOffset();

};
#endif
