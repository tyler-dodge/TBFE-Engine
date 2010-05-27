#include "Quaternion.h"
Quaternion::Quaternion(float newX,float newY,float newZ,float angle)
{
  angle*=DEG_RAD;
  w=cos(angle/2);
  x=newX*sin(angle/2);
  y=newY*sin(angle/2);
  z=newZ*sin(angle/2);
};
void Quaternion::normalize()
{
  float magnitude=sqrt(pow(x,2)+pow(y,2)+pow(z,2)+pow(w,2));
  x/=magnitude;
  y/=magnitude;
  z/=magnitude;
  w/=magnitude;
};
Matrix Quaternion::toMatrix()
{
  normalize();
  Matrix newMatrix(1-2*pow(y,2)-2*pow(z,2),  2*x*y+2*w*z,              2*x*z-2*w*y,             0,
		   2*x*y-2*w*z,              1-2*pow(x,2)-2*pow(z,2),  2*y*z+2*w*x,             0,
		   2*x*z+2*w*y,              2*y*z-2*w*x,              1-2*pow(x,2)-2*pow(y,2), 0,
		   0,                        0,                        0,                       1);
  return newMatrix;
};
Quaternion::Quaternion()
{
  x=0;
  y=0;
  z=0;
  w=1;
};
Quaternion Quaternion::operator*(Quaternion nQ)
{
  Quaternion finalQuaternion;
  finalQuaternion.w = nQ.w*w - nQ.x*x - nQ.y*y - nQ.z*z;
  finalQuaternion.x = nQ.w*x + nQ.x*w + nQ.y*z - nQ.z*y;
  finalQuaternion.y = nQ.w*y + nQ.y*w + nQ.z*x - nQ.x*z;
  finalQuaternion.z = nQ.w*z + nQ.z*w + nQ.x*y - nQ.y*x;
  return finalQuaternion;
};
PositionF Quaternion::operator*(PositionF point)
{
  Matrix rotations=toMatrix();
  PositionF newPoint;
  newPoint.X=rotations[0]*point.X+rotations[1]*point.Y+rotations[2]*point.Z;
  newPoint.Y=rotations[4]*point.X+rotations[5]*point.Y+rotations[6]*point.Z;
  newPoint.Z=rotations[8]*point.X+rotations[9]*point.Y+rotations[10]*point.Z;
  return newPoint;
};
void Quaternion::operator*=(Quaternion nQ)
{
  float fw = nQ.w*w - nQ.x*x - nQ.y*y - nQ.z*z;
  float fx = nQ.w*x + nQ.x*w + nQ.y*z - nQ.z*y;
  float fy = nQ.w*y + nQ.y*w + nQ.z*x - nQ.x*z;
  float fz = nQ.w*z + nQ.z*w + nQ.x*y - nQ.y*x;
  x=fx;
  y=fy;
  z=fz;
  w=fw;
};
