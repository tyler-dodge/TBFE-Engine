#include "Pulse.h"
Pulse::Pulse(int x, int y,int z, float size, PositionF angle, float distance):Actor(x,y)
{
  addCollisionBox(PositionF(0.0f,0.0f,0.0f),PositionF(size,size,size));
  setPosition(x,y,z);
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
  direction.X=size;
  direction.Y=0;
  direction.Z=0;
  collision->setRotation(rotation.X,rotation.Y,rotation.Z);
  direction=collision->applyRotations(direction);
  for(int i=0;i<distance_/size;i++)
    {      
      PositionF position=getPositionF();
      position+=direction*i;
      cout << position.dumpString() << '\n';
      int actor=checkActorCollision(position.X,position.Y,position.Z);  
      if (actor!=-1)
	{
	  cout << "Position: " << position.dumpString() << ':' << actor << '\n';
	};
    };
  return -1;
};
string Pulse::getConversation(bool PlayerCheck)
{
};
