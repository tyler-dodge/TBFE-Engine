#include "Quaternion.h"
Quaternion::Quaternion(float newX,float newY,float newZ,float angle)
{
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
  float tX=x;
  float tY=y;
  float tZ=z;
  float tW=-w;
  Matrix newMatrix(1-2*pow(tY,2)-2*pow(tZ,2), 2*tX*tY-2*tW*tZ, 2*tX*tZ+2*tW*tY, 0,
		   2*tX*tY+2*tW*tZ, 1-2*pow(tX,2)-2*pow(tZ,2), 2*tY*tZ-2*tW*tX, 0,
		   2*tX*tZ-2*tW*tY, 2*tY*tZ-2*tW*tX, 1-2*pow(tX,2)-2*pow(tY,2), 0,
		   0,           0,           0,                       1);
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
void Quaternion::operator*=(Quaternion nQ)
{
  float fw=w*nQ.w-x*nQ.x-y*nQ.y-z*nQ.z;
  float fx=w*nQ.x+x*nQ.w+y*nQ.z-z*nQ.y;
  float fy=w*nQ.y-x*nQ.z+y*nQ.w+z*nQ.x;
  float fz=w*nQ.z+x*nQ.y-y*nQ.x+z*nQ.w;
};
