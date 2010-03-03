#include "Actor.h"
#define PI 3.14159265
Actor::Actor (int PositionX,int PositionY)
    {
      currentAction_=NULL;
      setWalking(false);
      setMobile(true);
      actionList_.resize(0);
      setPosition(PositionX,0,PositionY);
      setName("None");
      setSpeed(5);
      setRotationF(0,0,0);
      string WalkAnimationBody="0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,";
      string WalkHeads="0,";
      Action Walk("Walk","");
      Animation Body("test.dae",WalkAnimationBody,
		     0,0,1,true);
      Body.setRotation(270,0,90);
      Walk.addAnimation(Body);
      Walk.setMainAnimation(0);
      addAction(Walk);
      PositionF position;
      position.X=-0.7;
      position.Y=-1.8;
      position.Z=0;
      PositionF dimensions;
      dimensions.X=1;
      dimensions.Y=2;
      dimensions.Z=2;
      addCollisionBox(position,dimensions);
      setBaseAction("Walk");
    };
PositionF Actor::getRotationF()
{
  return rotation_;
};
void Actor::addCollisionBox(PositionF position,PositionF dimensions)
{
  CollisionBox newCollision(position,dimensions);
  collisionMaps_.push_back(newCollision);
};
CollisionBox Actor::getCollisionBox(int num)
{
  if (num>collisionMaps_.size() || num<0)
    {
      cout << "collision Map goes past bounds\n";
      return collisionMaps_.at(0);
    };
  return collisionMaps_.at(num);
};
void Actor::setRotationF(float x,float y, float z)
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
int Actor::changePosition(float newAngle,bool ChangeDirection)
{
  if (rotation_.Z!=newAngle && ChangeDirection==true)
    {
      rotation_.Z=newAngle;
    };
  if (getCurrentAction().getName()!="Walk")
    {
      startAction("Walk");
    }
  setWalking(true);
  PositionF position;
  position=getPositionF();
  position.X+=(float)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
  position.Z-=(float)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
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
  setPositionF(position.X,position.Y,position.Z);
  vector<CollidedTile> collisionTest=TBFE_Base::CurrentMap.collisionTest((int)position_.X,
									 (int)position_.Y);
  if (collisionTest.size()>0)
    {
      for (int i=0;i<collisionTest.size();i++)
	{
	  bool AdvancedCollision=false;
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
		  position.X-=(float)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
		  position.Z+=(float)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
		  break;
		};
	      setPositionF(position.X,position.Y,position.Z);
	      return -2;
	    };
	};
    };
  int ncollisionTest=checkActorCollision(position.X,position.Y,position.Z);
  if (ncollisionTest!=-1)
    {
      position.X-=(float)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
      position.Z+=(float)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
      setPositionF(position.X,position.Y,position.Z);
      return ncollisionTest;
    };
  return -1;
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
  position_.X=(float)x;
  position_.Y=(float)y;
  position_.Z=(float)z;
};
void Actor::setPositionF(float x,float y,float z)
{
  position_.X=x;
  position_.Y=y;
  position_.Z=z;
};
int Actor::checkActorCollision(float offsetX,float offsetY,float offsetZ)
{
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      Actor * targetActor=TBFE_Base::ActorList.at(i);
      CollisionBox targetCollision=targetActor->getCollisionBox(0);
      if (targetActor!=this)
	{
	  for (int a=0;a<collisionMaps_.size();a++)
	    {
	      PositionF targetPosition=targetActor->getPositionF();
	      PositionF offset;
	      offset.X=offsetX-targetPosition.X;
	      offset.Y=offsetY-targetPosition.Y;
	      offset.Z=offsetZ-targetPosition.Z;
	      cout << "offsetPosition:" <<offsetX << "," << offsetY << "," << offsetZ << ":";
	      cout << "targetActor Position:" << targetPosition.X << "," << targetPosition.Y << "," << targetPosition.Z << "\n";
	      cout << "offset:" << offset.X << "," << offset.Y << "," << offset.Z << "\n";
	      PositionF targetRotation=targetActor->getRotationF();
	      targetCollision.setRotation(targetRotation.X,targetRotation.Y,targetRotation.Z);
	      collisionMaps_.at(a).setRotation(rotation_.X,rotation_.Y,rotation_.Z);
	      if (collisionMaps_.at(a).checkCollision(targetCollision,offset))
		{
		  return a;
		};
	    };
	};
    };
  return -1;
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
  offset.X=0;
  offset.Y=-1;
  return offset;
};
PositionF Actor::getPositionF()
{
  return position_;
};
