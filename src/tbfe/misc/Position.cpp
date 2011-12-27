#include "tbfe/misc/Position.h"
template<class T>
Position<T>::Position()
{
  X=0;
  Y=0;
  Z=0;
};
template<class T>
Position<T>::Position(T x,T y,T z)
{
  X=x;
  Y=y;
  Z=z;
};
template<class T>
Position<T> Position<T>::operator+(Position<T> newPosition)
{
  newPosition.X+=X;
  newPosition.Y+=Y;
  newPosition.Z+=Z;
  return newPosition;
};
template<class T>
Position<T> Position<T>::operator+(T a)
{
  Position<T> newPosition;
  newPosition.X=X+a;
  newPosition.Y=Y+a;
  newPosition.Z=Z+a;
  return newPosition;
};
template<class T>
Position<T> Position<T>::operator-(Position<T> newPosition)
{
  newPosition.X-=X;
  newPosition.Y-=Y;
  newPosition.Z-=Z;
  return newPosition;
};
template<class T>
void Position<T>::operator+=(Position<T> newPosition)
{
  X+=newPosition.X;
  Y+=newPosition.Y;
  Z+=newPosition.Z;
};
template<class T>
void Position<T>::operator-=(Position<T> newPosition)
{
  X-=newPosition.X;
  Y-=newPosition.Y;
  Z-=newPosition.Z;
};
template<class T>
Position<T> Position<T>::operator*(T num)
{
  Position<T> newPosition;
  newPosition.X=X*num;
  newPosition.Y=Y*num;
  newPosition.Z=Z*num;
  return newPosition;
};
template<class T>
Position<T> Position<T>::operator/(T num)
{
  Position<T> newPosition;
  newPosition.X=X/num;
  newPosition.Y=Y/num;
  newPosition.Z=Z/num;
  return newPosition;
};
template<class T>
string Position<T>::dumpString()
{
  std::stringstream text;
  text << '(' << X << ',' << Y << ',' << Z << ')';
  return text.str();
};
template<class T>
Position<T> Position<T>::operator*(Matrix matrix)
{
  Position<T> position;
  position.X=X*matrix[0]+Y*matrix[1]+Z*matrix[2];
  position.Y=X*matrix[4]+Y*matrix[5]+Z*matrix[6];
  position.Z=X*matrix[8]+Y*matrix[9]+Z*matrix[10];
  return position;
};

template class Position<int>;
template class Position<float>;
