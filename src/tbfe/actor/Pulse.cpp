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
  direction.X=0;
  direction.Y=0;
  direction.Z=size*20;
  collision->setRotation(rotation.X,-rotation.Y,rotation.Z);
  //cout << rotation.dumpString() << '\n';
  direction=applyRotations(direction,rotation);
  PositionF tempDirection;
  //tempDirection.X=direction.Z;
  //tempDirection.Y=direction.Y;
  //tempDirection.Z=direction.X;
  //direction=tempDirection;
  vector<int> ignore;
  //cout << direction.dumpString() << '\n';
  ignore.push_back(0);
  for(int i=0;i<distance_/(size*20);i++)
    {      
      PositionF position=getPositionF();
      position+=direction*i;
      //cout << position.dumpString() << '\n';
      int actor=checkActorCollision(position.X,position.Y,position.Z,&ignore);  
      stringstream evalText;
      evalText << "pulsePosition=Misc.PositionF();pulsePosition.X=" << position.X;
      evalText << ";pulsePosition.Y=" << position.Y;
      evalText << ";pulsePosition.Z=" << position.Z;
      TBFE_Base::MainConsole.runLine(evalText.str());
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
