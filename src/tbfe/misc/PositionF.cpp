#include "PositionF.h"
PositionF::PositionF()
{
  X=0;
  Y=0;
  Z=0;
};
PositionF::PositionF(float x,float y,float z)
{
  X=x;
  Y=y;
  Z=z;
};
PositionF PositionF::operator+(PositionF newPosition)
{
  newPosition.X+=X;
  newPosition.Y+=Y;
  newPosition.Z+=Z;
  return newPosition;
};
PositionF PositionF::operator+(float a)
{
  PositionF newPosition;
  newPosition.X=X+a;
  newPosition.Y=Y+a;
  newPosition.Z=Z+a;
  return newPosition;
};
PositionF PositionF::operator-(PositionF newPosition)
{
  newPosition.X-=X;
  newPosition.Y-=Y;
  newPosition.Z-=Z;
  return newPosition;
};
void PositionF::operator+=(PositionF newPosition)
{
  X+=newPosition.X;
  Y+=newPosition.Y;
  Z+=newPosition.Z;
};
void PositionF::operator-=(PositionF newPosition)
{
  X-=newPosition.X;
  Y-=newPosition.Y;
  Z-=newPosition.Z;
};
PositionF PositionF::operator*(float num)
{
  PositionF newPosition;
  newPosition.X=X*num;
  newPosition.Y=Y*num;
  newPosition.Z=Z*num;
  return newPosition;
};
PositionF PositionF::operator/(float num)
{
  PositionF newPosition;
  newPosition.X=X/num;
  newPosition.Y=Y/num;
  newPosition.Z=Z/num;
  return newPosition;
};
string PositionF::dumpString()
{
  std::stringstream text;
  text << '(' << X << ',' << Y << ',' << Z << ')';
  return text.str();
};
PositionF PositionF::operator*(Matrix matrix)
{
  PositionF position;
  position.X=X*matrix[0]+Y*matrix[1]+Z*matrix[2];
  position.Y=X*matrix[4]+Y*matrix[5]+Z*matrix[6];
  position.Z=X*matrix[8]+Y*matrix[9]+Z*matrix[10];
  return position;
};
