#include "tbfe/map/TileLayer.h"
TileLayer::TileLayer()
{
  dimensions_.X=0;
  dimensions_.Y=0;
  data_.resize(0);
};
TileLayer::TileLayer(int width, int height)
{
  dimensions_.X=width;
  dimensions_.Y=height;
  data_.resize(width*height);
};
PositionI TileLayer::getDimensions()
{
  return dimensions_;
};
Tile TileLayer::getTile(int x,int y)
{
  PositionI Dimensions;
  Dimensions=getDimensions();
  if (x < 0 || y < 0 || x >= Dimensions.X || y >= Dimensions.Y)
    {
      Tile BlankTile;
      BlankTile.Passability=0;
      BlankTile.TileSet=0;
      BlankTile.Type=NONE;
      return BlankTile;
    };
  Tile tile=data_.at(x+y*Dimensions.X);
  return tile;
};
void TileLayer::changeTile(int x,int y,Tile newTile)
{
  PositionI Dimensions;
  Dimensions=getDimensions();
  if (x>Dimensions.X || y > Dimensions.Y || x < 0 || y < 0)
    {
      return;
    };
  data_.at(x+y*Dimensions.X)=newTile;
};
void TileLayer::generateMap(int x,int y,Tile newTile)
{
  data_.resize(0);
  data_.resize(x*y);
  dimensions_.X=x;
  dimensions_.Y=y;
  for (int i=0;i<x*y;i++)
    {
      data_.at(i)=newTile;
    };
};
bool TileLayer::getVisibility()
{
  return isVisible_;
};
void TileLayer::setVisibility(bool newVisibility)
{
  isVisible_=newVisibility;
};
//TODO: getVisibility, setVisibility
