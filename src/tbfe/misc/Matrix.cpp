#include "tbfe/misc/Matrix.h"
Matrix::Matrix()
{
  for (int i=0;i<16;i++)
    {
      data_[i]=0;
    };
};
Matrix::Matrix(float a00,float a01,float a02,float a03,
	       float a10,float a11,float a12,float a13,
	       float a20,float a21,float a22,float a23,
	       float a30,float a31,float a32,float a33)
{
  data_[0]=a00;
  data_[1]=a01;
  data_[2]=a02;
  data_[3]=a03;
  data_[4]=a10;
  data_[5]=a11;
  data_[6]=a12;
  data_[7]=a13;
  data_[8]=a20;
  data_[9]=a21;
  data_[10]=a22;
  data_[11]=a23;
  data_[12]=a30;
  data_[13]=a31;
  data_[14]=a32;
  data_[15]=a33;
};
Matrix Matrix::operator*(Matrix multMatrix)
{
  float newData[16];
  for (int y=0;y<4;y++)
    {
      for (int x=0;x<4;x++)
	{
	  newData[x+y*4]=data_[4*y]*multMatrix[x]+data_[4*y+1]*multMatrix[x+4]
	    +data_[4*y+2]*multMatrix[x+8]+data_[4*y+3]*multMatrix[x+12];
	};
    };
  Matrix newMatrix(newData[0],newData[1],newData[2],newData[3],
		   newData[4],newData[5],newData[6],newData[7],
		   newData[8],newData[9],newData[10],newData[11],
		   newData[12],newData[13],newData[14],newData[15]);
  return newMatrix;
}; 
void Matrix::operator*=(Matrix multMatrix)
{
  float newData[16];
  for (int y=0;y<4;y++)
    {
      for (int x=0;x<4;x++)
	{
	  newData[x+y*4]=data_[4*y]*multMatrix[x]+data_[4*y+1]*multMatrix[x+4]
	    +data_[4*y+2]*multMatrix[x+8]+data_[4*y+3]*multMatrix[x+12];
	};
    };
  for(int i=0;i<16;i++)
    {
      data_[i]=newData[i];
    };
}; 
float Matrix::operator[](int num)
{
  return data_[num];
};
PositionF Matrix::operator*(PositionF position)
{
  PositionF newPosition;
  newPosition.X=data_[0]*position.X+data_[1]*position.Y+data_[2]*position.Z;
  newPosition.Y=data_[4]*position.X+data_[5]*position.Y+data_[6]*position.Z;
  newPosition.Z=data_[8]*position.X+data_[9]*position.Y+data_[10]*position.Z;
  return newPosition;
};
void Matrix::Normalize()
{
  float magnitude;
  magnitude=sqrt(pow(data_[0],2)+pow(data_[1],2)+pow(data_[2],2));
  data_[0]/=magnitude;
  data_[1]/=magnitude;
  data_[2]/=magnitude;
  magnitude=sqrt(pow(data_[4],2)+pow(data_[5],2)+pow(data_[6],2));
  data_[4]/=magnitude;
  data_[5]/=magnitude;
  data_[6]/=magnitude;
  magnitude=sqrt(pow(data_[8],2)+pow(data_[9],2)+pow(data_[10],2));
  data_[8]/=magnitude;
  data_[9]/=magnitude;
  data_[10]/=magnitude;
};
string Matrix::dumpString()
{
  stringstream newString;
  for (int y=0;y<4;y++)
    {
      for (int x=0;x<4;x++)
	{
	  newString << data_[x+y*4] << ":      ";
	};
      newString << '\n';
    };
  return newString.str();
};
Matrix::Matrix(float x,float y,float z)
{ 
};
float * Matrix::dataPointer()
{
  return data_;
};
void Matrix::fromGlMatrix(float * glArray)
{
  for (int i=0;i<16;i++)
    {
      data_[i]=glArray[i];
    };
};
Matrix::Matrix(float x,float y,float z,float angle)
{
  angle*=DEG_RAD;
  float c=cos(angle);
  float s=sin(angle);
  float t=1-cos(angle);
  data_[0]=t*pow(x,2)+c;
  data_[1]=t*x*y-s*z;
  data_[2]=t*x*z+s*y;
  data_[3]=0;

  data_[4]=t*x*y+s*z;
  data_[5]=pow(y,2)*t+c;
  data_[6]=t*y*z-s*x;
  data_[7]=0;

  data_[8]=t*x*z-s*y;
  data_[9]=t*y*z+s*x;
  data_[10]=t*pow(z,2)+c;
  data_[11]=0;

  data_[12]=0;
  data_[13]=0;
  data_[14]=0;
  data_[15]=1;
};
