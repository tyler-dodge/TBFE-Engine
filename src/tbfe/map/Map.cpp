#include "Map.h"
Map::Map()
{
  layers_.resize(0);
  plantTypes_.resize(0);
};
Map::~Map()
{
};
void Map::loadPlants(std::string FileName)
{ 
  ifstream PlantData(FileName.c_str(),ifstream::binary);
  if (PlantData==NULL)
    {
      TBFE_Base::MainConsole.errorMessage(0,FileName);
      return;
    };
  
  bool EndLoop=false;
  int i=0;
  while (i<100)
    {
      i++;
      std::string PlantName=loadString(&PlantData,':');
      if (PlantName=="")
	{
	  return;
	};
      int PlantStates=atoi(loadString(&PlantData,',').c_str());
      if (PlantStates==0)
	{
	  TBFE_Base::MainConsole.write("Plant Type "+PlantName+" ended prematurely in States");
	  return;
	};
      int PlantStateLength=atoi(loadString(&PlantData,',').c_str());
      if (PlantStateLength==0)
	{
	  TBFE_Base::MainConsole.write("Plant Type "+PlantName+" ended prematurely in Duration");
	  return;
	};
      int PlantItem=atoi(loadString(&PlantData,';').c_str());
      if (PlantItem==0)
	{
	  TBFE_Base::MainConsole.write("Plant Type "+PlantName+" ended prematurely in Item");
	  return;
	};
      loadString(&PlantData,'\n');
      addPlantType(PlantName,PlantStates,PlantStateLength,PlantItem);
    };
};
void Map::addPlantType(string Name, int NumberOfStates, int StateDuration,int PlantItem)
{
  Plant newType;
  newType.Increase=1/(double)StateDuration;
  newType.Level=0;
  newType.FinalLevel=NumberOfStates;
  newType.Type=(PlantType)PlantItem;
  plantTypes_.push_back(newType);
};
void Map::generateMap(int x,int y)
{
  tileSetNames_.resize(0);
  tileSetNames_.push_back("FarmTiles.png");
  TileLayer newLayer(x,y);
  Tile newTile;
  newTile.Type=DIRT;
  newTile.TileSet=0;
  newTile.Passability=0;
  newTile.PlantInfo.Type=(PlantType)-1;
  newLayer.generateMap(x,y,newTile);
  addLayer(newLayer);
};
bool Map::loadMap(string filename)
{
  ifstream NewMapData(filename.c_str(),ifstream::binary);
  if (NewMapData==NULL)
    {
      return false;
    };
  Position dimensions;
  dimensions.X=NewMapData.get();
  dimensions.Y=NewMapData.get();
  scriptFile_=loadString(&NewMapData,(char)3);
  tileSetNames_.resize(NewMapData.get());
  for (int TileSetsNum=0;TileSetsNum<tileSetNames_.size();TileSetsNum++)
    {
      tileSetNames_.at(TileSetsNum)=loadString(&NewMapData,(char)3);
    };
  string LayerString=loadString(&NewMapData,'|');
  do
    {
      TileLayer newLayer(dimensions.X,dimensions.Y);
      for (int FillMap=0;FillMap<dimensions.X*dimensions.Y;FillMap++)
	{
	  Tile newTile;
	  newTile.TileSet=(int)nextChar(&LayerString);
	  newTile.Type=(TileType)nextChar(&LayerString);
	  newTile.PlantInfo=setPlantData((PlantType)nextChar(&LayerString));
	  newTile.PlantInfo.Level=(double)nextChar(&LayerString)/100;
	  newTile.Passability=(int)nextChar(&LayerString);
	  newLayer.changeTile(FillMap-FillMap/dimensions.X*dimensions.X,FillMap/dimensions.X,newTile);
	};
      addLayer(newLayer);
      string LayerString=loadString(&NewMapData,'|');
    } while (LayerString!="");
  TBFE_Base::MainConsole.write("Map Scripts");
  TBFE_Base::MainConsole.write("===========");
  TBFE_Base::MainConsole.execute("Maps/"+scriptFile_);
  TBFE_Base::MainConsole.write("===========");
  return true;
};
bool Map::dumpMap(string filename)
{
  Position dimensions=layers_.at(0).getDimensions();
  ofstream NewMapData(filename.c_str(),ofstream::binary);
  NewMapData.put((char)dimensions.X);
  NewMapData.put((char)dimensions.Y);
  NewMapData.write(scriptFile_.c_str(),scriptFile_.size());
  NewMapData.put((char)3);
  NewMapData.put((char)tileSetNames_.size());
  for (int i=0;i<tileSetNames_.size();i++)
    {
      NewMapData.write(tileSetNames_.at(i).c_str(),tileSetNames_.at(i).size());
      NewMapData.put((char)3);
    };
	  //Layer
  for (int Layer=0;Layer<getNumberOfLayers();Layer++)
    {
      for (int i=0;i<dimensions.X*dimensions.Y;i++)
	{
	  Tile saveTile=getTile(i-i/dimensions.X*dimensions.X,i/dimensions.X,Layer);
	  NewMapData.put((char)saveTile.TileSet);
	  NewMapData.put((char)saveTile.Type);
	  NewMapData.put((char)saveTile.PlantInfo.Number);
	  NewMapData.put((char)((saveTile.PlantInfo.Level)*100));
	  NewMapData.put((char)saveTile.Passability);
	};
      NewMapData.put('|');
    };
  return true;
};
vector<CollidedTile> Map::collisionTest(int x,int y)
{
  vector<CollidedTile> tiles;
  CollidedTile newTile;
  int tile;
  if ((tile=getTile(x/100,y/100,0).Passability)!=0)
    {
      newTile.Passability=tile;
      newTile.position.X=(x/100)*100;
      newTile.position.Y=(y/100)*100;
      tiles.push_back(newTile);
    }
  if ((tile=getTile(x/100,y/100+1,0).Passability)!=0)
    {
      newTile.Passability=tile;
      newTile.position.X=(x/100)*100;
      newTile.position.Y=(y/100+1)*100;
      tiles.push_back(newTile);
    }
  if ((tile=getTile(x/100+1,y/100,0).Passability)!=0)
    {
      newTile.Passability=tile;
      newTile.position.X=(x/100+1)*100;
      newTile.position.Y=(y/100)*100;
      tiles.push_back(newTile);
    }
  if ((tile=getTile(x/100+1,y/100+1,0).Passability)!=0)
    {
      newTile.Passability=tile;
      newTile.position.X=(x/100+1)*100;
      newTile.position.Y=(y/100+1)*100;
      tiles.push_back(newTile);
    };
   return tiles;
};
Plant Map::setPlantData(PlantType Type)
{
  Plant TempPlant;
  if (Type>plantTypes_.size() || Type==NO_PLANT)
    {
      if (Type!=NO_PLANT)
	{;
	  TBFE_Base::MainConsole.write("  Plant Data exceeds size of Plant Types");
	};
      TempPlant.Type=Type;
      TempPlant.Number=NO_PLANT;
      return TempPlant;
    };
  TempPlant=plantTypes_.at(Type-1);
  TempPlant.Number=Type;
  return TempPlant;
};
void Map::changeTile(int x,int y, Tile newTile,int Layer)
{
  if (Layer>layers_.size() || Layer<0)
    {
      return;
    };
  layers_.at(Layer).changeTile(x,y,newTile);
};
void Map::addTileSet(string newTileSet)
{
  tileSetNames_.push_back(newTileSet);
};
Position Map::getDimensions()
{
  return layers_.at(0).getDimensions();
};
Tile Map::getTile(int x,int y, int Layer)
{
  return layers_.at(Layer).getTile(x,y);
};
void Map::addLayer(TileLayer newLayer)
{
  layers_.push_back(newLayer);
};
bool Map::getLayerVisibility(int layer)
{
  return layers_.at(layer).getVisibility();
};
void Map::setLayerVisibility(int layer,bool newVisibility)
{
  layers_.at(layer).setVisibility(newVisibility);
};
int Map::getNumberOfLayers()
{
  return layers_.size();
};
string Map::getTileSet(int tileSetNum)
{
  return tileSetNames_.at(tileSetNum);
};
int Map::getNumberOfTileSets()
{
  return tileSetNames_.size();
};
