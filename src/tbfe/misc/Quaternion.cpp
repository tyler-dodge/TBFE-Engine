#include "Quaternion.h"
Quaternion::Quaternion(float newX,float newY,float newZ,float angle)
{
  x=x;
  y=y;
  z=z;
  w=cos(angle/2);
  x=x*sin(angle/2);
  y=y*sin(angle/2);
  z=z*sin(angle/2);
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
  Matrix newMatrix(1-2*pow(y,2)-2*pow(z,2), 2*x*y-2*w*z, 2*x*z+2*w*y, 0,
		   2*x*y+2*w*z, 1-2*pow(x,2)-2*pow(z,2), 2*y*z-2*w*x, 0,
		   2*x*z-2*w*y, 2*y*z-2*w*x, 1-2*pow(x,2)-2*pow(y,2), 0,
		   0,                             0,                         0, 1);
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
  finalQuaternion.w=w*nQ.w-x*nQ.x-y*nQ.y-z*nQ.z;
  finalQuaternion.x=w*nQ.x+x*nQ.w+y*nQ.z-z*nQ.y;
  finalQuaternion.y=w*nQ.y-x*nQ.z+y*nQ.w+z*nQ.x;
  finalQuaternion.z=w*nQ.z+x*nQ.y-y*nQ.x+z*nQ.w;
  return finalQuaternion;
};
