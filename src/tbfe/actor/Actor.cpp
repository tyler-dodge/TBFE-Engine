#include "Actor.h"
#define PI 3.14159265
Actor::Actor (int PositionX,int PositionY)
    {
      currentAction_=NULL;
      setCollisionMap("Actors/living/Collision.png");
      setWalking(false);
      setMobile(true);
      actionList_.resize(0);
      setCollisionDimensions(40,60,170);
      setPosition(PositionX,PositionY);
      setName("None");
      setSpeed(1);
      setAngle(0);
      string WalkAnimationBody="0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,";
      string WalkHeads="0,";
      Action Walk("Walk","");
      Animation Body("test.dae",WalkAnimationBody,
		     100,200,-30,-140,1,true);
      Walk.addAnimation(Body);
      Walk.setMainAnimation(0);
      addAction(Walk);
      setBaseAction("Walk");
    };
int Actor::getAngle()
{
  return angle_;
};
PositionD Actor::getRotationD()
{
  return rotation_;
};
void Actor::setRotationD(double x,double y, double z)
{
  rotation_.X=x;
  rotation_.Y=y;
  rotation_.Z=z;
};
string Actor::getProperty(string propertyName)
{
  for (int i=0;i<propertyList_.size();i++)
    {
      if (propertyList_.at(i).Name==propertyName)
	{
	  return propertyList_.at(i).Value;
	};
    };
  return "";
};
void Actor::setProperty(string propertyName,string newValue)
{
  for (int i=0;i<propertyList_.size();i++)
    {
      if (propertyList_.at(i).Name==propertyName)
	{
	  propertyList_.at(i).Value=newValue;
	  return;
	};
    };
  Property newProperty;
  newProperty.Name=propertyName;
  newProperty.Value=newValue;
  propertyList_.push_back(newProperty);
};
Action Actor::getCurrentAction()
{
  if (currentAction_==NULL)
    {
      Action NoAction;
      NoAction=*getAction(getBaseAction());
      NoAction.setName("None");
      NoAction.setScript("");
      return NoAction;
    };
  return *currentAction_;
};
bool Actor::runAction()
{
  if (currentAction_==NULL)
    {
      return false;      
    };
  //currentAction_->setDirection(getDirection());
  if (!currentAction_->animationPlus())
    {
      endCurrentAction();
      return false;
    };
  return true;
};
bool Actor::addAction(Action newAction)
{
  for (int i=0;i<actionList_.size();i++)
    {
      if (actionList_.at(i).getName()==newAction.getName())
	{
	  actionList_.at(i)=newAction;
	  newAction.loadAnimation();
	  return true;
	};
    };
  newAction.loadAnimation();
  actionList_.push_back(newAction);
  return true;
};
bool Actor::startAction(string actionName)
{
  currentAction_=getAction(actionName);
  return false;
};
Action * Actor::getAction(string actionName)
{
  for (int i=0;i<actionList_.size();i++)
    {
      if (actionList_.at(i).getName()==actionName)
	{
	  return &actionList_.at(i);
	};
    };
  return NULL;
};
bool Actor::endCurrentAction()
{
  if (currentAction_!=NULL)
    {
      currentAction_->reset();
      if (currentAction_->getScript()!="")
	{
	  stringstream endScriptParams;
	  endScriptParams << "Caller=TBFE.GetActorByNum(" << TBFE_Base::GetActorNum(this) << ")";
	  TBFE_Base::MainConsole.runLine("Caller=nil");
	  TBFE_Base::MainConsole.runLine(endScriptParams.str());
	  TBFE_Base::MainConsole.runLine(currentAction_->getScript().c_str());
	};
      currentAction_=NULL;
    };
};
Actor::~Actor()
{
};
void Actor::setConversation(string text)
{
  conversation_=text;
};
void Actor::setAngle(int newAngle)
{
  angle_=newAngle;
};
int Actor::changePosition(int newAngle,bool ChangeDirection)
{
  if (getAngle()!=newAngle && ChangeDirection==true)
    {
      setAngle(newAngle);
    };
  if (getCurrentAction().getName()!="Walk")
    {
      startAction("Walk");
    }
  setWalking(true);
  PositionD position;
  position=getPositionD();
  position.X+=(double)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
  position.Z+=(double)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
  //switch(NewDirection)
  // {
  //  case UP:
  //    position.Y-=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
  //    break;
  // case RIGHT:
  //    position.X+=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
  //    break;
  //  case DOWN:
  //   position.Y+=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
  //   break;
  //  case LEFT:
  //    position.X-=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
  //    break;
  //  };
  setPositionD(position.X,position.Y,position.Z);
  vector<CollidedTile> collisionTest=TBFE_Base::CurrentMap.collisionTest((int)position_.X,
									 (int)position_.Y);
  if (collisionTest.size()>0)
    {
      for (int i=0;i<collisionTest.size();i++)
	{
	  Position TileOffset;
	  Position tile=collisionTest.at(i).position;
	  SDL_Rect actorRect=getCollisionRect();
	  TileOffset.X=-tile.X+position.X;
	  TileOffset.Y=-tile.Y+position.Y;
	  if (actorRect.h>100)
	    {
	      TileOffset.Y-=100;
	    };
	  SDL_Rect tileRect;
	  tileRect.x=0;
	  tileRect.y=0;
	  tileRect.h=100;
	  tileRect.w=100;
	  bool AdvancedCollision=advancedCollision(TBFE_Base::GetCollisionTile(),
						   tileRect,TileOffset);
	  if (AdvancedCollision)
	    {
	      switch(collisionTest.at(i).Passability)
		{
		case 199:
		  if (ChangeDirection==true)
		    {
		      TBFE_Base::MainConsole.runLine("if ChangeForeground~=Nil then ChangeForeground(0) end");
		    };
		  break;
		case 200:
		  if (ChangeDirection==true)
		    {
		      TBFE_Base::MainConsole.runLine("if ChangeForeground~=Nil then ChangeForeground(1) end");
		    };
		  break;
		case 255:
		  position.X-=(double)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
		  position.Y-=(double)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
		  break;
		};
	      setPositionD(position.X,position.Y,position.Z);
	      return -2;
	    };
	};
    };
  int ncollisionTest=checkActorCollision((int)position.X,
					 (int)position.Y,true);
  if (ncollisionTest!=-1)
    {
      position.X-=(double)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
      position.Y-=(double)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
      setPositionD(position.X,position.Y,position.Z);
      return ncollisionTest;
    };
  return -1;
};
void Actor::changeScreen(int MapWidth, int MapHeight)
{
  switch(getAngle())
    {
    case 180:
      position_.X=MapWidth*100-50;
      break;
    case 90:
      position_.Y=MapHeight*100-100;
      break;
    case 0:
      position_.X=10;
      break;
    case 270:
      position_.Y=10;
      break;
    };
};
Position Actor::getPosition()
{
  Position PlayerPosition;
  PlayerPosition.X=(int)position_.X;
  PlayerPosition.Y=(int)position_.Y;
  PlayerPosition.Z=(int)position_.Z;
  return PlayerPosition;
};
void Actor::setPosition(int x,int y,int z)
{
  position_.X=(double)x;
  position_.Y=(double)y;
  position_.Z=(double)z;
};
void Actor::setPositionD(double x,double y,double z)
{
  position_.X=x;
  position_.Y=y;
  position_.Z=z;
};
bool Actor::advancedCollision(SDL_Surface * ColliderMap,SDL_Rect ColliderRect,Position ColliderOffset)
{
  SDL_Rect selfRect=getCollisionRect();
  //TODO: collisionMap Lock
  if (ColliderMap!=NULL && collisionMap_!=NULL)
    {
      Uint32 aColor=SDL_MapRGB(ColliderMap->format,255,255,255);
      for (int y=0;y<=selfRect.h;y+=2)
	{
	  for (int x=0;x<=selfRect.w;x+=2)
	    {
	      if (getPixel(collisionMap_,x+selfRect.x,y+selfRect.y)==aColor)
		{							 
		  if (x+ColliderOffset.X>=0 && y+ColliderOffset.Y>=0 &&
		      x+ColliderOffset.X<=ColliderMap->w/2 && y+ColliderOffset.Y<=ColliderMap->h/2)
		    {
		      int pixX=x+ColliderOffset.X+ColliderRect.x;
		      int pixY=y+ColliderOffset.Y+ColliderRect.y;
		      if (getPixel(ColliderMap,pixX,pixY)==aColor)
			{
			  return true;
			}
		    };
		};
	    };
	};
    };
  return false;
};
int Actor::checkActorCollision(bool useAdvancedCollision,int OffsetX,int OffsetY)
{
  int ActorNumber=TBFE_Base::GetActorNum(this);
  SDL_Rect selfArea=getCollisionRect();
  Position selfPosition=getPosition();
  for (int i=TBFE_Base::ActorList.size()-1;i>=0;i--)
    { 
      Actor * iActor=TBFE_Base::ActorList.at(i);
      Position iPosition=iActor->getPosition();
      SDL_Rect iArea=iActor->getCollisionRect();
      if ((iPosition.X<=selfPosition.X && 
	   iPosition.X+iArea.w>=selfPosition.X &&
	   iPosition.Y<=selfPosition.Y &&
	   iPosition.Y+iArea.h>=selfPosition.Y) ||
	  
	  (selfPosition.X<=iPosition.X && 
	   selfPosition.X+selfArea.w>=iPosition.X &&
	   selfPosition.Y<=iPosition.Y &&
	   selfPosition.Y+selfArea.h>=iPosition.Y) ||
	  
	  (selfPosition.X<=iPosition.X+iArea.w &&
	   selfPosition.X+selfArea.w>=iPosition.X+iArea.w &&
	   selfPosition.Y<=iPosition.Y+iArea.h &&
	   selfPosition.Y+selfArea.h>=iPosition.Y+iArea.h)	||
	  
	  (iPosition.X<=selfPosition.X+selfArea.w &&
	   iPosition.X+iArea.w>=selfPosition.X+selfArea.w &&
	   iPosition.Y<=selfPosition.Y+selfArea.h &&
	   iPosition.Y+iArea.h>=selfPosition.Y+selfArea.h) || 
	  
	  (selfPosition.X<=iPosition.X+iArea.w &&
	   selfPosition.X+selfArea.w>=iPosition.X+iArea.w &&
	   selfPosition.Y<=iPosition.Y+iArea.h &&
	   selfPosition.Y+selfArea.h>=iPosition.Y)	||
	  
	  (iPosition.X<=selfPosition.X+selfArea.w &&
	   iPosition.X+iArea.w>=selfPosition.X+selfArea.w &&
	   iPosition.Y<=selfPosition.Y+selfArea.h &&
	   iPosition.Y+iArea.h>=selfPosition.Y)) 
	{
	  Position selfDimensions=getCollisionDimensions();
	  Position iDimensions=iActor->getCollisionDimensions();
	  if ((selfDimensions.Z+selfPosition.Z>=iPosition.Z && 
	       selfDimensions.Z+selfPosition.Z<=iPosition.Z+iDimensions.Z) ||
	    (iPosition.Z+iDimensions.Z>=selfPosition.Z &&	      
	     iPosition.Z+iDimensions.Z<=selfPosition.Z+selfDimensions.Z))
	    {
	      if (i!=ActorNumber)
		{	
		  Position iOffset;
		  iOffset.X=selfPosition.X-iPosition.X;
		  iOffset.Y=selfPosition.Y-iPosition.Y;
		  if (useAdvancedCollision)
		    {
		      //TODO: iActor Collision Map Lock
		      if (advancedCollision(iActor->getCollisionMap(),iArea,iOffset))
			{
			  return i;
			};
		    }
		  else
		    {
		      return i;
		    };
		};
	    };
	};
    };
  return -1;
};
SDL_Rect Actor::getCollisionRect()
{
  SDL_Rect collisionRect;
  Position dimensions;
  dimensions=getCollisionDimensions();
  collisionRect.x=0;
  collisionRect.y=0;
  collisionRect.w=dimensions.X;
  collisionRect.h=dimensions.Y;
  return collisionRect;
};
SDL_Surface * Actor::getCollisionMap()
{
  //TODO: collision Map Lock
  if (collisionMap_==NULL)
    {
      //TODO: collisionSource_ Lock
      collisionMap_=TBFE_Base::CheckSheets(collisionSource_);
    };
  return collisionMap_;
};
void Actor::setCollisionMap(string source)
{ 
  SDL_Surface * newCollision;
  newCollision=TBFE_Base::CheckSheets(source);
  if (newCollision==NULL)
    {
      return;
    };
  collisionMap_=newCollision;
  collisionSource_=source;
};
int Actor::getSpeed()
{
  return speed_;
};
void Actor::setSpeed(int newSpeed)
{
  speed_=newSpeed;
};
string Actor::getScriptSource()
{
  return scriptSource_;
};
void Actor::setScriptSource(string newScript)
{
  scriptSource_=newScript;
};
string Actor::getName()
{
  return name_;
};
void Actor::setName(string newName)
{
  name_=newName;
};
string Actor::getBaseAction()
{
  return baseAction_;
};
void Actor::setBaseAction(string newBaseAction)
{
  if (getAction(newBaseAction)==NULL)
    {
      TBFE_Base::MainConsole.write(newBaseAction+" does not exist.");
      return;
    };
  baseAction_=newBaseAction;
};
Position Actor::getCollisionDimensions()
{
  return collisionDimensions_;
};
void Actor::setCollisionDimensions(int x,int y, int z)
{
  collisionDimensions_.X=x;
  collisionDimensions_.Y=y;
  collisionDimensions_.Z=z;
};
bool Actor::getWalking()
{
  return isWalking_;
};
void Actor::setWalking(bool newWalking)
{
  isWalking_=newWalking;
};
bool Actor::getMobile()
{
  return isMobile_;
};
void Actor::setMobile(bool newMobility)
{
  isMobile_=newMobility;
};

Position Actor::getDirOffset()
{
  Position offset;
  switch (getAngle())
    {
    case 90:
      offset.X=0;
      offset.Y=-1;
      break;
    case 0:
      offset.X=1;
      offset.Y=0;
      break;
    case 270:
      offset.X=0;
      offset.Y=1;
      break;
    case 180:
      offset.X=-1;
      offset.Y=0;
      break;
    };
  return offset;
};
void Actor::loadCollisionMap(string newSource)
{
  SDL_Surface * newCollision=TBFE_Base::CheckSheets(newSource);
  if (newCollision==NULL)
    {
      return;
    };
  collisionSource_=newSource;
  collisionMap_=newCollision;
};
PositionD Actor::getPositionD()
{
  return position_;
};
