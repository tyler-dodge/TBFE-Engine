class Matrix;
#ifndef Matrix_L
#define Matrix_L
#include <math.h>
#include "tbfe/misc/Quaternion.h"
#include <sstream>
#include "Enums.h"
#include <string>
using namespace std;
class Matrix
{
 private:
  float data_[16];
 public:
  Matrix();
  Matrix(float,float,float,float,
	 float,float,float,float,
	 float,float,float,float,
	 float,float,float,float);
  Matrix(float,float,float); //from Euler angles
  Matrix(float,float,float,float); //from axis-angle
  Matrix operator*(Matrix);
  void fromGlMatrix(float *);
  void operator*=(Matrix);
  PositionF operator*(PositionF);
  float * dataPointer();
  void Normalize();
  float operator[](int);
  string dumpString();
};
#endif
