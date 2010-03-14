#include "CollisionBox.h"
CollisionBox::CollisionBox(PositionF offset,PositionF dimensions)
{
  position_=offset;
  dimensions_=dimensions;
  setRotation(0,0,0);
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
float CollisionBox::convertToAngle(float x,float y)
{
  float addAngle=0;
  if (x==0 && y>0)
    {
      return PI/2;
    }
  else if (x==0 && y<0)
    {
      return 3*PI/2;
    };
  float absX=x;
  float absY=y;
  if (x<0)
    {
      absX*=-1;
    };
  if (y<0)
    {
      absY*=-1;
    };
  float angle=atan(absY/absX);
  if (y>=0 && x<0)
    {
      angle=PI-angle;
    }
  else if (y<0 && x<0)
    {
      angle=PI+angle;
    }
  else if (y<0 && x>=0)
    {
      angle=2*PI-angle;
    }
  else
    {
    };
  return angle;
};
PositionF CollisionBox::applyRotations(PositionF position)
{
  float magnitude=sqrt(pow(position.Y,2)+pow(position.Z,2));
  PositionF tempPosition=position;
  //X rotation
  if (position.Y!=0)
    {
      position.Y=cos(convertToAngle(position.Y,position.Z)+rotation_.X*PI/180)*magnitude;
      position.Z=sin(convertToAngle(position.Y,position.Z)+rotation_.X*PI/180)*magnitude;
    };
  tempPosition=position;
  magnitude=sqrt(pow(position.X,2)+pow(position.Z,2));
  //Y rotation
  if (position.X!=0)
    {
      position.X=cos(convertToAngle(tempPosition.X,tempPosition.Z)+rotation_.Y*PI/180)*magnitude;
      position.Z=sin(convertToAngle(tempPosition.X,tempPosition.Z)+rotation_.Y*PI/180)*magnitude;
    };
  tempPosition=position;
  magnitude=sqrt(pow(position.X,2)+pow(position.Y,2));
  //Z rotation
   if (position.X!=0)
    {
      position.X=cos(convertToAngle(position.X,position.Y)+rotation_.Z*PI/180)*magnitude;
      position.Y=sin(convertToAngle(position.X,position.Y)+rotation_.Z*PI/180)*magnitude;
   };
  return position;
};
bool CollisionBox::checkLine(float x1,float y1,float x2,float y2,float checkX,float checkY,float centerX,float centerY)
{
  PositionF position;
  position.X=x1;
  position.Y=y1;
  PositionF position2;
  position2.X=x2;
  position2.Y=y2;
  PositionF checkPoint;
  checkPoint.X=checkX;
  checkPoint.Y=checkY;
  PositionF centerPoint;
  centerPoint.X=centerX;
  centerPoint.Y=centerY;
  if (fabs(position2.Y-position.Y)>fabs(position2.X-position.X))
    {
      float m=(position2.X-position.X)/(position2.Y-position.Y);
      //cout << "check set 1:" << position.X << ":" << centerPoint.dumpString();
      
      float tempX=m*(checkPoint.Y-position.Y)+position.X;
      float centerCheckX=m*(centerPoint.Y-position.Y)+position.X;
      if ((checkPoint.X>tempX && centerPoint.X>centerCheckX) ||
	  (checkPoint.X<tempX && centerPoint.X<centerCheckX))
	{
	  return true;
	};
      return false;
    };
  float m=(position2.Y-position.Y)/(position2.X-position.X);
  float tempY=m*(checkPoint.X-position.X)+position.Y;
  float centerCheckY=m*(centerPoint.X-position.X)+position.Y;
  //cout << "check set horizontal:";
  //cout << "tempY:" << tempY << ":" << centerPoint.Y << ":" << position.dumpString() << ":chkpt>ty:" << (checkPoint.Y>tempY) << ": cp>ty:" << (centerCheckY>tempY) << ": chkpt<ty:" << (checkPoint.Y<tempY) << ": cp<ty:" << (centerPoint.Y<centerCheckY) << ":";
  if ((checkPoint.Y>tempY && centerPoint.Y>centerCheckY) ||
      (checkPoint.Y<tempY && centerPoint.Y<centerCheckY))
    {
      return true;
    };
  return false;
};
vector<PositionF> CollisionBox::generatePoints(PositionF position,PositionF dimensions)
{
  vector<PositionF> thisPoint;
  thisPoint.resize(8);
  thisPoint[0]=position;


  thisPoint[1]=position;
  thisPoint[1].X+=dimensions.X;

  thisPoint[2]=position;
  thisPoint[2].X+=dimensions.X;
  thisPoint[2].Z+=dimensions.Z;

  thisPoint[3]=position;
  thisPoint[3].Z+=dimensions.Z;

  thisPoint[4]=position;
  thisPoint[4].Y+=dimensions.Y;

  thisPoint[5]=position;
  thisPoint[5].X+=dimensions.X;
  thisPoint[5].Y+=dimensions.Y;

  thisPoint[6]=position+dimensions;

  thisPoint[7]=position;
  thisPoint[7].Z+=dimensions.Z;
  thisPoint[7].Y+=dimensions.Y;
  for (int i=0;i<8;i++)
    {
      thisPoint[i]=applyRotations(thisPoint[i]);
    };			
  return thisPoint;
};
bool CollisionBox::checkCollision(CollisionBox target,PositionF targetOffset,bool crossCheck)
{
  PositionF position=position_;
  PositionF dimensions=dimensions_;
  PositionF targetPosition=target.getPosition();
  PositionF targetDimensions=target.getDimensions();

  vector<PositionF> thisPoint;
  vector<PositionF> targetPoint;
  thisPoint=generatePoints(position,dimensions);
  targetPoint=target.generatePoints(targetPosition,targetDimensions);
  for (int i=0;i<8;i++)
    {
      targetPoint[i]-=targetOffset/20.0f;
    };
  PositionF centerPoint;
  centerPoint.X=0;
  centerPoint.Y=0;
  centerPoint.Z=0;
  centerPoint=(thisPoint[0]+thisPoint[2])/2;
  // cout << "set\n";
  for (int currentPoint=0;currentPoint<4;currentPoint++)
    {
      //cout << targetPoint.at(currentPoint).dumpString() << "  pointset\n";
      bool collision=true;
      for (int i=0;i<4;i++)
	{
	  int a=i+1;
	  bool isGreater=false;
	  if (i==3)
	    {
	      a=0;
	    };
	  //cout << i << ":";
	  if (!checkLine(thisPoint[i].X,thisPoint[i].Z,thisPoint[a].X,thisPoint[a].Z,targetPoint.at(currentPoint).X,targetPoint.at(currentPoint).Z,centerPoint.X,centerPoint.Z))
	    {
	      //cout << "fail";
	      collision=false;
	    };
	  //cout << '\n';
	};
      //cout << "pointset End\n";
      if (collision)
	{
	  return true;
	};
    };
  if (crossCheck)
    {
      targetOffset.X*=-1;
      targetOffset.Y*=-1;
      targetOffset.Z*=-1;
      return target.checkCollision(*this,targetOffset,false);
    };
  return false;
};
