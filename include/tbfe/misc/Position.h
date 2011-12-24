template <class T>
class Position;
typedef Position<float> PositionF;
typedef Position<int> PositionI;
#ifndef PositionF_L
#define PositionF_L
#include <boost/python.hpp>
#include <string>
#include<sstream>
#include "Matrix.h"
class Matrix;
using namespace std;
template <class T>
class Position
{
 public:
  T X;
  T Y;
  T Z;
  Position<T>();
  Position<T>(T x,T y,T z);
  Position<T> operator+(Position<T> newPosition);
  Position<T> operator+(T a);
  Position<T> operator-(Position<T> newPosition);
  void operator+=(Position<T> newPosition);
  void operator-=(Position<T> newPosition);
  Position<T> operator*(T num);
  Position<T> operator/(T num);
  string dumpString();
  PositionF operator*(Matrix matrix);
};
#endif
