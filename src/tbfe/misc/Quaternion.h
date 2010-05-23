#include<math.h>
class Quaternion;
#ifndef Quaternion_L
#define Quaternion_L
struct Quaternion
{
public:
  float x,y,z,w;
  Quaternion();
  Quaternion(float,float,float,float);
  Matrix toMatrix();
  Quaternion operator*(Quaternion);
  //PositionF operator*(PositionF);
  //Quaternion conj();
  void normalize();
};
#endif
