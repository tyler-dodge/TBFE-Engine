#include "Actor.h"
Actor::Actor (int PositionX,int PositionY)
    {
      setCollisionMap("Actors/living/Collision.png");
      setWalking(false);
      setMobile(true);
      actionList_.resize(0);
      currentAction_=NULL;
      setCollisionDimensions(40,60,170);
      setPosition(PositionX,PositionY);
      setName("None");
      setBaseAction("Walk");
      setSpeed(5);
      setDirection(DOWN);
      string WalkAnimationBody="0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,,";
      string WalkHeads="0,";
      Action Walk("Walk","");
      Animation Body("Actors/living/body/normal/walk.png",WalkAnimationBody,
		     100,200,-30,-140,1,true);
      Animation Shirt("Actors/living/torso/white_tshirt/walk.png",WalkAnimationBody,
		      100,200,-30,-140,1,true);
      Animation Legs("Actors/living/legs/jeans/walk.png",WalkAnimationBody,
		     100,200,-30,-140,1,true);
      Animation Head("Actors/living/head/head.png",WalkHeads,
		     100,200,-30,-140,1,true);
      Walk.addAnimation(Head);
      Walk.addAnimation(Body);
      Walk.addAnimation(Shirt);
      Walk.addAnimation(Legs);
      Walk.setMainAnimation(1);
      addAction(Walk);
    };
Action Actor::getCurrentAction()
{
  if (currentAction_==NULL)
    {
      Action NoAction;
      NoAction=*getAction(getBaseAction());
      NoAction.setDirection(getDirection());
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
  currentAction_->setDirection(getDirection());
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
	  endScriptParams << "Caller=TBFE.GetActorByNum(" << GetActorNum(this) << ")";
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
void Actor::setDirection(Direction NewDirection)
{
  direction_=NewDirection;
};
int Actor::changePosition(Direction NewDirection,bool ChangeDirection)
{
  if (getDirection()!=NewDirection && ChangeDirection==true)
    {
      setDirection(NewDirection);
    };
  if (getCurrentAction().getName()!="Walk")
    {
      startAction("Walk");
    }
  setWalking(true);
  PositionF position;
  position=getPositionF();
  switch(NewDirection)
    {
    case UP:
      position.Y-=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
      break;
    case RIGHT:
      position.X+=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
      break;
    case DOWN:
      position.Y+=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
      break;
    case LEFT:
      position.X-=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
      break;
    };
  int SizeX;
  int SizeY;
  if (getDirection()==DOWN || getDirection()==UP)
    {
      SizeX=collisionDimensions_.X;
      SizeY=collisionDimensions_.Y;
    }
  else
    {
      SizeX=collisionDimensions_.Y;
      SizeY=collisionDimensions_.X;
    };
  setPositionF(position.X,position.Y,position.Z);
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
	  bool AdvancedCollision=advancedCollision(TBFE_Base::CollisionTile,
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
		  switch(getDirection())
		    {
		    case UP:
		      position.Y+=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
		      break;
		    case RIGHT:
		      position.X-=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
		      break;
		    case DOWN:
		      position.Y-=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
		      break;
		    case LEFT:
		      position.X+=fabs((float)getSpeed()*TBFE_Base::GameSpeed);
		      break;
		    };
		  break;
		};
	      setPositionF(position.X,position.Y,position.Z);
	      return -2;
	    };
	};
    };
  int ncollisionTest=checkActorCollision((int)position.X,
					 (int)position.Y,true);
  if (ncollisionTest!=-1)
    {
      Direction oppositeDirection;
      switch (getDirection())
	{
	case LEFT:
	  oppositeDirection=RIGHT;
	  break;
	case UP:
	  oppositeDirection=DOWN;
	  break;
	case RIGHT:
	  oppositeDirection=LEFT;
	  break;
	case DOWN:
	  oppositeDirection=UP;
	  break;
	};
      setPositionF(position.X,position.Y,position.Z);
      changePosition(oppositeDirection,false);
      return ncollisionTest;
    };
  return -1;
};
void Actor::changeScreen(int MapWidth, int MapHeight)
{
  switch(getDirection())
    {
    case LEFT:
      position_.X=MapWidth*100-50;
      break;
    case UP:
      position_.Y=MapHeight*100-100;
      break;
    case RIGHT:
      position_.X=10;
      break;
    case DOWN:
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
Direction Actor::getDirection()
{
  return direction_;
};
void Actor::setPosition(int x,int y,int z)
{
  position_.X=(float)x;
  position_.Y=(float)y;
  position_.Z=(float)z;
};
void Actor::setPositionF(float x,float y,float z)
{
  position_.X=(float)x;
  position_.Y=(float)y;
  position_.Z=(float)z;
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
  int ActorNumber=GetActorNum(this);
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
  collisionRect.x=(getDirection()-(int)(getDirection()/2)*2)*dimensions.X;
  collisionRect.y=(int)((int)getDirection()/2)*dimensions.Y;
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
  switch (getDirection())
    {
    case UP:
      offset.X=0;
      offset.Y=-1;
      break;
    case RIGHT:
      offset.X=1;
      offset.Y=0;
      break;
    case DOWN:
      offset.X=0;
      offset.Y=1;
      break;
    case LEFT:
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
PositionF Actor::getPositionF()
{
  return position_;
};
