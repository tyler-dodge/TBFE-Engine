#include "SunVector.h"
SunVector::SunVector(int x,int y,int angle)
{
  Speed=5;
  Angle=angle;
  CurrentPositionX=x;
  CurrentPositionY=y;
};
SunVector::SunVector()
{
  Speed=5;
  Angle=10;
  CurrentPositionX=5;
  CurrentPositionY=5;
};
void SunVector::Calculate(int Multiplier)
{
  CurrentPositionX+=cos(Angle* M_PI / 180)*Speed*Multiplier; //
  CurrentPositionY+=sin(Angle* M_PI / 180)*Speed*Multiplier;
};
