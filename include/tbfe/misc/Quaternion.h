struct Quaternion;
#ifndef Quaternion_L
#define Quaternion_L
#include <boost/python.hpp>
#include<math.h>
#include "tbfe/misc/PositionF.h"
struct Quaternion
{
public:
  float x,y,z,w;
  Quaternion();
  Quaternion(float,float,float,float);
  Matrix toMatrix();
  Quaternion operator*(Quaternion);
  void operator*=(Quaternion);
  PositionF operator*(PositionF);
  //Quaternion conj();
  void normalize();
};
#endif
