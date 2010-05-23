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
  collision->setRotation(rotation.X,rotation.Y,rotation.Z);
  //cout << rotation.dumpString() << '\n';
  direction=applyRotations(direction,rotation);
  PositionF tempDirection;
  //tempDirection.X=direction.Z;
  //tempDirection.Y=direction.Y;
  //tempDirection.Z=direction.X;
  //direction=tempDirection;
  //cout << direction.dumpString() << '\n';
  for(int i=0;i<distance_/(size*20);i++)
    {      
      PositionF position=getPositionF();
      position+=direction*i;
      //cout << position.dumpString() << '\n';
      vector<int> actor=checkActorCollision(position.X,position.Y,position.Z);  
      int currentActor=-1;
      float currentDistance=0;
      for (int i=0;i<actor.size();i++)
	{
	  Actor * targetActor=TBFE_Base::GetActorByNum(actor.at(i));
	  if (targetActor!=NULL && targetActor!=TBFE_Base::GetMainPlayer())
	    {
	      PositionF targetActorPos=targetActor->getPositionF();
	      PositionF startPos=getPositionF();
	      PositionF difference=targetActorPos-startPos;
	      float distance=sqrt(pow(difference.X,2)+pow(difference.Y,2)+pow(difference.Z,2));
	      if (distance>currentDistance)
		{
		  currentActor=actor.at(i);
		};
	    };
	};
      stringstream evalText;
      evalText << "pulsePosition=Misc.PositionF();pulsePosition.X=" << position.X;
      evalText << ";pulsePosition.Y=" << position.Y;
      evalText << ";pulsePosition.Z=" << position.Z;
      TBFE_Base::MainConsole.runLine(evalText.str());
      if (actor.size()!=0)
	{
	  return currentActor;
	};
    };
  return -1;
};
string Pulse::getConversation(bool PlayerCheck)
{
};
