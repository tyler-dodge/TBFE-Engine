#include "CollisionBox.h"
CollisionBox::CollisionBox(PositionF offset,PositionF dimensions)
{
  position_=offset;
  dimensions_=dimensions;
};
PositionF CollisionBox::getDimensions()
{
  return dimensions_;
};
void CollisionBox::setDimensions(float x,float y,float z)
{
  dimensions_.X=x;
  dimensions_.Y=y;
  dimensions_.Z=z;
};

PositionF CollisionBox::getPosition()
{
  return position_;
};
void CollisionBox::setPosition(float x,float y,float z)
{
  position_.X=x;
  position_.Y=y;
  position_.Z=z;
};

PositionF CollisionBox::getRotation()
{
  return rotation_;
};
void CollisionBox::setRotation(float x,float y,float z)
{
  rotation_.X=x;
  rotation_.Y=y;
  rotation_.Z=z;
};
PositionF CollisionBox::applyRotations(PositionF position)
{
  //X rotation
  cout << position.Z << ":" << position.Y << ":" <<atan(position.Z/position.Y) << "\n";
  if (position.Y!=0)
    {
      position.Y=cos(atan(position.Z/position.Y)+rotation_.X*PI/180)*sqrt(pow(position.Y,2)+pow(position.Z,2));
      position.Z=sin(atan(position.Z/position.Y)+rotation_.X*PI/180)*sqrt(pow(position.Y,2)+pow(position.Z,2));
    };
  //Y rotation
  if (position.X!=0)
    {
      position.X=cos(atan(position.Z/position.X)+rotation_.Y*PI/180)*sqrt(pow(position.X,2)+pow(position.Z,2));
      position.Z=sin(atan(position.Z/position.X)+rotation_.Y*PI/180)*sqrt(pow(position.X,2)+pow(position.Z,2));
    };
  //Z rotation
  if (position.X!=0)
    {
      position.X=cos(atan(position.Y/position.X)+rotation_.Z*PI/180)*sqrt(pow(position.X,2)+pow(position.Y,2));
      position.Y=sin(atan(position.Y/position.X)+rotation_.Z*PI/180)*sqrt(pow(position.X,2)+pow(position.Y,2));
    };
  return position;
};
bool CollisionBox::checkCollision(CollisionBox target,PositionF offset)
{
  PositionF thisPosition=applyRotations(position_);
  PositionF thisDimensions=applyRotations(dimensions_);
  PositionF targetPosition=target.getPosition();
  PositionF targetDimensions=target.getDimensions();
  targetPosition=target.applyRotations(targetPosition);
  targetDimensions=target.applyRotations(targetDimensions);
  targetPosition.X+=offset.X/20;
  targetPosition.Y+=offset.Y/20;
  targetPosition.Z+=offset.Z/20;
  //cout<<"target position:"<< targetPosition.X <<','<< targetPosition.Y <<','<< targetPosition.Z << "\n";
  //cout << offset.X <<  ',' <<offset.Y << ',' <<offset.Z << "\n";
  if (((targetPosition.X<=thisPosition.X &&
	targetPosition.X+targetDimensions.X>=thisPosition.X) ||
       (thisPosition.X<=targetPosition.X &&
	thisPosition.X+thisDimensions.X>=targetPosition.X) ||
       (thisPosition.X<=targetPosition.X+targetDimensions.X &&
	thisPosition.X+thisDimensions.X>=targetPosition.X+targetDimensions.X) ||
       (targetPosition.X<=thisPosition.X+thisDimensions.X &&
	targetPosition.X+targetDimensions.X>=thisPosition.X+thisDimensions.X)) &&

      ((targetPosition.Y<=thisPosition.Y &&
	targetPosition.Y+targetDimensions.Y>=thisPosition.Y) ||
       (thisPosition.Y<=targetPosition.Y &&
	thisPosition.Y+thisDimensions.Y>=targetPosition.Y) ||
       (thisPosition.Y<=targetPosition.Y+targetDimensions.Y &&
	thisPosition.Y+thisDimensions.Y>=targetPosition.Y+targetDimensions.Y) ||
       (targetPosition.Y<=thisPosition.Y+thisDimensions.Y &&
	targetPosition.Y+targetDimensions.Y>=thisPosition.Y+thisDimensions.Y)) &&

      ((targetPosition.Z<=thisPosition.Z &&
	targetPosition.Z+targetDimensions.Z>=thisPosition.Z) ||
       (thisPosition.Z<=targetPosition.Z &&
	thisPosition.Z+thisDimensions.Z>=targetPosition.Z) ||
       (thisPosition.Z<=targetPosition.Z+targetDimensions.Z &&
	thisPosition.Z+thisDimensions.Z>=targetPosition.Z+targetDimensions.Z) ||
       (targetPosition.Z<=thisPosition.Z+thisDimensions.Z &&
	targetPosition.Z+targetDimensions.Z>=thisPosition.Z+thisDimensions.Z)))
    {
      return true;
    };
  return false;
};
