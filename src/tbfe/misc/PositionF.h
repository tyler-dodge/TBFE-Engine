#include <string>
struct PositionF;
#ifndef PositionF_L
#define PositionF_L
class Matrix;
using namespace std;
struct PositionF
{
  float X;
  float Y;
  float Z;
  PositionF();
  PositionF(float x,float y,float z);
  PositionF operator+(PositionF newPosition);
  PositionF operator+(float a);
  PositionF operator-(PositionF newPosition);
  void operator+=(PositionF newPosition);
  void operator-=(PositionF newPosition);
  PositionF operator*(float num);
  PositionF operator/(float num);
  string dumpString();
  PositionF operator*(Matrix matrix);
};
#endif
