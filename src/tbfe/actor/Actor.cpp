#include "Actor.h"
Actor::Actor (int PositionX,int PositionY)
    {
      currentAction_=NULL;
      actionList_.resize(0);
      setPositionF(PositionX,0,PositionY);
      setName("None");
      setSpeed(5);
      
      Action Stand("Stand","");
      addAction(Stand);
      setBaseAction("Stand");
    };
Quaternion Actor::getRotation()
{
  return rotation_;
};
void Actor::addCollisionBox(PositionF position,PositionF dimensions)
{
  CollisionBox newCollision(position,dimensions);
  collisionMaps_.push_back(newCollision);
};
int Actor::getNumCollisionBox()
{
  return collisionMaps_.size();
};
CollisionBox * Actor::getCollisionBox(int num)
{
  if (num>=collisionMaps_.size() || num<0)
    {
      TBFE_Base::MainConsole.write("collision number goes past array size");
      if (num==0)
	{
	  TBFE_Base::MainConsole.write("new collision box created at 0");
	  PositionF collPos;
	  collPos.X=0;
	  collPos.Y=0;
	  collPos.Z=0;
	  PositionF collSize;
	  collSize.X=1;
	  collSize.Y=1;
	  collSize.Z=1;
	  addCollisionBox(collPos,collSize);
	};
      return &collisionMaps_.at(0);
    };
  return &collisionMaps_.at(num);
};
void Actor::setRotation(Quaternion rotations)
{
  rotation_=rotations;
};
void Actor::rotate(Quaternion rotations,bool doCollisionTest)
{
  Quaternion oldRotation=rotation_;
  rotation_*=rotations;
  if (doCollisionTest)
    {
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
		    case 255:
		      rotation_=oldRotation;
		      break;
		    };
		};
	    };
	};
      vector<int> ncollisionTest=checkActorCollision(position_.X,position_.Y,position_.Z);
      if (ncollisionTest.size()!=0)
	{
	  rotation_=oldRotation;
	};
    };
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
int Actor::changePosition(float newAngle)
{
  if (getCurrentAction().getName()!="Walk")
    {
      startAction("Walk");
    }
  setProperty("walk","1");
  PositionF position;
  PositionF direction(0,0,1);
  float magnitude;
  position=getPositionF();
  Quaternion rotations(0,1,0,newAngle);
  rotations*=rotation_;
  direction=applyRotations(direction,rotations);
  direction.X*=-1;
  magnitude=sqrt(pow(direction.X,2)+pow(direction.Z,2));
  direction=direction/magnitude;
  position.X+=speed_*direction.X;
  position.Z+=speed_*direction.Z;
  //position.X+=(float)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
  //position.Z-=(float)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
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
		case 255:
		  position.X-=speed_*direction.X;
		  position.Z-=speed_*direction.Z;
		  //position.X-=(float)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
		  //position.Z+=(float)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
		  break;
		};
	      setPositionF(position.X,position.Y,position.Z);
	      return -2;
	    };
	};
    };
  vector<int> ncollisionTest=checkActorCollision(position.X,position.Y,position.Z);
  if (ncollisionTest.size()!=0)
    {
      position.X-=(float)getSpeed()*direction.X;
      position.Z-=(float)getSpeed()*direction.Z;
      //position.X-=(float)getSpeed()*TBFE_Base::GameSpeed*cos(newAngle*PI/180);
      //position.Z+=(float)getSpeed()*TBFE_Base::GameSpeed*sin(newAngle*PI/180);
      setPositionF(position.X,position.Y,position.Z);
      return -2;
    };
  return -1;
};
void Actor::setPositionF(float x,float y,float z)
{
  position_.X=x;
  position_.Y=y;
  position_.Z=z;
};
vector<int> Actor::checkActorCollision(float offsetX,float offsetY,float offsetZ)
{
  vector<int> collisions;
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      Actor * targetActor=TBFE_Base::ActorList.at(i);
      for (int targetA=0;targetA<targetActor->getNumCollisionBox();targetA++)
	{
	  CollisionBox targetCollision=*targetActor->getCollisionBox(targetA);
	  if (targetActor!=this && targetCollision.checkEnabled())
	    {
	      for (int a=0;a<collisionMaps_.size();a++)
		{
		  PositionF targetPosition=targetActor->getPositionF();
		  PositionF offset;
		  offset.X=offsetX-targetPosition.X;
		  offset.Y=offsetY-targetPosition.Y;
		  offset.Z=offsetZ-targetPosition.Z;
		  Quaternion targetRotation=targetActor->getRotation();
		  Quaternion tempRotation=rotation_;
		  targetRotation.w*=-1;
		  tempRotation.w*=-1;
		  targetCollision.setRotation(targetRotation);
		  collisionMaps_.at(a).setRotation(rotation_);
		  if (collisionMaps_.at(a).checkCollision(targetCollision,offset))
		    {
		      collisions.push_back(i);
		    };
		};
	    };
	};
    };
  return collisions;
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

PositionF Actor::getPositionF()
{
  return position_;
};
