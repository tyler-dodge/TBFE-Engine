#include "OverMap.h"
OverMap::OverMap(int NewWidth,int NewHeight)
{
  width=NewWidth;
  height=NewHeight;
  MapLocations=new string[width*height];
  currentPosition.X=1;
  currentPosition.Y=1;
};
OverMap::~OverMap()
{
  delete [] MapLocations;
};
void OverMap::SetPoint(int x,int y,std::string Source)
{
  MapLocations[x+y*width]=Source;
}
string OverMap::PlayerMove(Direction MoveDirection)
{
  switch(MoveDirection)
    {
    case LEFT:
      currentPosition.X-=1;
      break;
    case UP:
      currentPosition.Y-=1;
      break;
    case RIGHT:
      currentPosition.X+=1;
      break;
    case DOWN:
      currentPosition.Y+=1;
      break;
    };
  return getPoint(currentPosition.X,currentPosition.Y);
};
string OverMap::getPoint(int x,int y)
{
  if (x>width || y>height || x<0 || y <0)
    {
      return NULL;
    };
  return MapLocations[x+y*width]; 
};
Position OverMap::GetPosition()
{
  return currentPosition;
};
void OverMap::SetPosition(int x, int y)
{
  currentPosition.X=x;
  currentPosition.Y=y;
};
int OverMap::GetWidth()
{
  return width;
};
int OverMap::GetHeight()
{
  return height;
};
