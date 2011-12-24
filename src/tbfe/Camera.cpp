#include "tbfe/Camera.h"
Camera::Camera(PositionF _offset,PositionF _followOffset,Quaternion _angle) :
  offset(_offset),followOffset(_followOffset),angle(_angle)
{
  
}
Camera::Camera():
  offset(),followOffset(),angle()
{
}
PositionF Camera::getOffset()
{
  return offset;
}
PositionF Camera::getFollowOffset()
{
  return followOffset;
}
Quaternion Camera::getAngle()
{
  return angle;
}
