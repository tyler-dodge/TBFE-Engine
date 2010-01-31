#include "Building.h"
Building::Building(string Map,string FloorMap,string RoofMap,int x,int y)
{
  setPosition(x/100,y/100);
  int StartX=x;
  do
    {
      string Row=nextSet(&Map,';');
      do
	{
	  nextSet(&Row,'"');
	  string Type=nextSet(&Row,'"');
	  if (Type!=" ")
	    {
	      nextSet(&Row,':');
	      int direction=atoi(nextSet(&Row,',').c_str());
	      Actor * newActor=createActor(x,y,Type,Type,"building",false);
	      if (newActor!=NULL)
		{
		  walls_.push_back(newActor);
		  walls_.at(walls_.size()-1)->setDirection((Direction)direction);
		};
	    }
	  else
	    {
	      nextSet(&Row,',');
	    };
	  x+=100;
	} while (Row.find(',')!=string::npos);
      x=StartX;
      y+=100;
    } while (Map.find(';')!=string::npos);
  setFloorDimensions(0,0);
  Position tempFloorDimensions=getFloorDimensions();
  do
    {
      string Row=nextSet(&FloorMap,';');
      int TempX=0;
      do
	{
	  string Type;
	  string TileSet;
	  Type=nextSet(&Row,':');
	  TileSet=nextSet(&Row,',');
	  Tile newTile;
	  newTile.Type=(TileType)atoi(Type.c_str());
	  newTile.TileSet=(TileType)(atoi(TileSet.c_str()));
	  newTile.Passability=0;
	  newTile.PlantInfo.Type=(PlantType)0;
	  floor_.push_back(newTile);
	  TempX++;
	} while (Row.find(',')!=string::npos);
      if (TempX>tempFloorDimensions.X)
	{
	  tempFloorDimensions.X=TempX;
	};
      tempFloorDimensions.Y+=1;
    } while (FloorMap.find(';')!=string::npos);
  setFloorDimensions(tempFloorDimensions.X,tempFloorDimensions.Y);
  setRoofDimensions(0,0);
  Position tempRoofDimensions=getRoofDimensions();
  do
    {
      string Row=nextSet(&RoofMap,';');
      int TempX=0;
      do
	{
	  string Type;
	  string TileSet;
	  Type=nextSet(&Row,':');
	  TileSet=nextSet(&Row,',');
	  Tile newTile;
	  newTile.Type=(TileType)atoi(Type.c_str());
	  newTile.TileSet=(TileType)(atoi(TileSet.c_str()));
	  newTile.Passability=0;
	  newTile.PlantInfo.Type=NO_PLANT;
	  roof_.push_back(newTile);
	  TempX++;
	} while (Row.find(',')!=string::npos);
      if (TempX>tempRoofDimensions.X)
	{
	  tempRoofDimensions.X=TempX;
	};
      tempRoofDimensions.Y++;
    } while (RoofMap.find(';')!=string::npos);
  setRoofDimensions(tempRoofDimensions.X,tempRoofDimensions.Y);
};
Building::~Building()
{
};
Tile Building::getFloorTile(int x,int y)
{
  Position floorDimensions=getFloorDimensions();
  if (x+y*floorDimensions.X>floor_.size())
    {
      Tile BlankTile;
      BlankTile.Passability=0;
      BlankTile.TileSet=0;
      BlankTile.Type=(TileType)-1;
      BlankTile.PlantInfo.Type=NO_PLANT;
      return BlankTile;
    };
  Tile returnTile=floor_.at(x+y*floorDimensions.X);
  return returnTile;
};
Tile Building::getRoofTile(int x,int y)
{
  Position roofDimensions=getRoofDimensions();
  if (x+y*roofDimensions.X>roof_.size())
    {
      Tile BlankTile;
      BlankTile.Passability=0;
      BlankTile.TileSet=0;
      BlankTile.Type=(TileType)-1;
      BlankTile.PlantInfo.Type=NO_PLANT;
      return BlankTile;
    };
  Tile returnTile=roof_.at(x+y*roofDimensions.X);
  return returnTile;
};
Position Building::getPosition()
{
  return position_;
};
void Building::setPosition(int x,int y)
{
  position_.X=x;
  position_.Y=y;
};
Position Building::getFloorDimensions()
{
  return floorDimensions_;
};
void Building::setFloorDimensions(int x,int y)
{
  floorDimensions_.X=x;
  floorDimensions_.Y=y;
};
Position Building::getRoofDimensions()
{
  return roofDimensions_;
};
void Building::setRoofDimensions(int x,int y)
{
  roofDimensions_.X=x;
  roofDimensions_.Y=y;
};
Actor * Building::getWall(int wallNumber)
{
  if (wallNumber<walls_.size())
    {
      return walls_.at(wallNumber);
    }
  else
    {
      return NULL;
    };
};
int Building::getNumberOfWalls()
{
  return walls_.size();
};
