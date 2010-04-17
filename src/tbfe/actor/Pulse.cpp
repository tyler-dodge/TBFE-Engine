#include "Pulse.h"
Pulse::Pulse(PositionF position, float size, PositionF angle, float distance):Actor(position.X,position.Z)
{
  addCollisionBox(PositionF(0.1f,0.0f,0.0f),PositionF(size,size,size));
  setPosition(position.X,position.Y,position.Z);
  setRotationF(angle.X,angle.Y,angle.Z);
  distance_=distance;
};
Pulse::~Pulse()
{
};
int Pulse::collisionPulse()
{
  CollisionBox * collision=getCollisionBox(0);
  PositionF direction;
  PositionF rotation=getRotationF();
  float size=collision->getDimensions().X;
  direction.X=size*20;
  direction.Y=0;
  direction.Z=0;
  collision->setRotation(rotation.X,rotation.Y,rotation.Z);
  direction=applyRotations(direction,rotation);
  PositionF tempDirection;
  //tempDirection.X=direction.Z;
  //tempDirection.Y=direction.Y;
  //tempDirection.Z=direction.X;
  //direction=tempDirection;
  cout << direction.dumpString() << '\n';
  vector<int> ignore;
  ignore.push_back(0);
  for(int i=0;i<distance_/(size*20);i++)
    {      
      PositionF position=getPositionF();
      position+=direction*i;
      int actor=checkActorCollision(position.X,position.Y,position.Z,&ignore);  
      if (actor!=-1)
	{
	  return actor;
	};
    };
  return -1;
};
string Pulse::getConversation(bool PlayerCheck)
{
};
