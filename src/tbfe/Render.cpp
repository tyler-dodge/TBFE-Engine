
#include "Render.h"
TBFE_Render::TBFE_Render()
{
  lightingPercentage_=20;
  TTF_Init();
  TBFE_Base::font=TTF_OpenFont("Images/UI/font.ttf",12);
  textColor_.r=255;
  textColor_.g=255;
  textColor_.b=255;
  screen_=SDL_SetVideoMode(TBFE_Base::ScreenDimensions.X,TBFE_Base::ScreenDimensions.Y,32,SDL_HWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
  collision_=TBFE_Base::CheckSheets("Images/UI/Collision.png");
  darkness_=TBFE_Base::CheckSheets("Images/Darkness.png");
  changeLighting(10);
  window_=TBFE_Base::CheckSheets("Images/UI/Window.png");
  TBFE_Base::CollisionTile=TBFE_Base::CheckSheets("Tile.png");
};
void TBFE_Render::init()
{
  screen_=SDL_SetVideoMode(TBFE_Base::ScreenDimensions.X,TBFE_Base::ScreenDimensions.Y,32,SDL_HWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
 };
TBFE_Render::~TBFE_Render()
{
  TTF_CloseFont(TBFE_Base::font);
  TTF_Quit();
  SDL_Quit();
};
void TBFE_Render::changeLighting(int NewValue)
{
  if (darkness_!=NULL)
    {
      SDL_SetAlpha(darkness_, SDL_SRCALPHA, NewValue);
    };
};
inline void TBFE_Render::initializeTileSets()
{
  //Tile Sets
  TBFE_Base::MainConsole.write("TileSets Loaded:");
  for(int i=0;i<tileSet_.size();i++)
    {
      SDL_FreeSurface(tileSet_.at(i));
    };
  tileSet_.resize(0);
  for (int i=0;i<TBFE_Base::CurrentMap.getNumberOfTileSets();i++)
    {
      string tempString="Images/TileSets/"+TBFE_Base::CurrentMap.getTileSet(i);
      TBFE_Base::MainConsole.write(tempString); 
      tileSet_.push_back(TBFE_Base::CheckSheets(tempString));
    };
};
void TBFE_Render::finalRender(bool doFlip)
{  
  Position ScreenPosition;
  Position CurrentPosition;
  CurrentPosition=TBFE_Base::MainPlayer->getPosition();
  offset_.X=TBFE_Base::ScreenDimensions.X/2-TBFE_Base::TileSize/2;
  offset_.Y=TBFE_Base::ScreenDimensions.Y/2; 
  if (offset_.X>CurrentPosition.X)
    {
      offset_.X=CurrentPosition.X;
    };
  if (offset_.Y>CurrentPosition.Y)
    {
      offset_.Y=CurrentPosition.Y;
    };
  Position mapDimensions=TBFE_Base::CurrentMap.getDimensions();
  if (offset_.Y+2*TBFE_Base::TileSize+CurrentPosition.Y>mapDimensions.Y*TBFE_Base::TileSize)
    {
      offset_.Y=CurrentPosition.Y-mapDimensions.Y*TBFE_Base::TileSize+TBFE_Base::ScreenDimensions.Y;
    };
  if (offset_.X+TBFE_Base::TileSize+CurrentPosition.X>mapDimensions.X*TBFE_Base::TileSize)
    {
      offset_.X=CurrentPosition.X-mapDimensions.X*TBFE_Base::TileSize+TBFE_Base::ScreenDimensions.X;
    };
  
  renderMapLayer(CurrentPosition.X-offset_.X,CurrentPosition.Y-offset_.Y,0);
  arrangeActors();
  renderActors();
  for (int i=1;i<TBFE_Base::CurrentMap.getNumberOfLayers();i++)
    {
      renderMapLayer(CurrentPosition.X-offset_.X,CurrentPosition.Y-offset_.Y,i);
    };
  renderWindowList();
  SDL_Rect Dark;
  Dark.x=0;
  Dark.y=0;
  Dark.w=TBFE_Base::ScreenDimensions.X;
  Dark.h=TBFE_Base::ScreenDimensions.Y;
  applyImage(0,0,darkness_,screen_,&Dark);
  if (doFlip)
    {
      SDL_Flip(screen_);
    };
};
void TBFE_Render::arrangeActors()
{
  vector<Actor *> tempActors;
  vector<Position> positions;
  vector<int> Order;
  Order.resize(0);
  positions.resize(TBFE_Base::ActorList.size());
  for(int getPos=0;getPos<TBFE_Base::ActorList.size();getPos++)
    {
      positions.at(getPos)=TBFE_Base::ActorList.at(getPos)->getPosition();
    };
  for (int x=0;x<positions.size();x++)
    {
      bool isInserted=false;
      for (int checkPositions=0;checkPositions<Order.size();checkPositions++)
	{
	  if (positions.at(x).Y<positions.at(checkPositions).Y && !isInserted)
	    {
	      Order.insert(Order.begin()+checkPositions,x);
	      isInserted=true;
	    };
	};
      if (isInserted==false)
	{
	  Order.push_back(x);
	};
    };
  int newPlayerNum;
  for (int i=0;i<Order.size();i++)
    {
      tempActors.push_back(TBFE_Base::ActorList.at(Order.at(i)));
    };
  TBFE_Base::ActorList=tempActors;
};
int TBFE_Render::renderMapLayer(int x,int y, int Layer)
{
    SDL_Rect TileRect;
    int TileNumber;
    for (int mapY=y/TBFE_Base::TileSize;mapY<y/TBFE_Base::TileSize+TBFE_Base::ScreenDimensions.Y/TBFE_Base::TileSize+1;mapY++)
      {
	for(int mapX=x/TBFE_Base::TileSize;mapX<x/TBFE_Base::TileSize+TBFE_Base::ScreenDimensions.X/TBFE_Base::TileSize+1;mapX++)
	  {
	    Tile tile=TBFE_Base::CurrentMap.getTile(mapX,mapY,Layer);
	    TileNumber=(int)tile.Type;
	    TileRect.x=(TileNumber-(int)(TileNumber/2)*2)*TBFE_Base::TileSize;
	    TileRect.y=(int)(TileNumber/2)*TBFE_Base::TileSize;
	    TileRect.w=TBFE_Base::TileSize;
	    TileRect.h=TBFE_Base::TileSize;
	    if (tile.TileSet<tileSet_.size())
	      {
		applyImage(mapX*TBFE_Base::TileSize-x,mapY*TBFE_Base::TileSize-y,
			   tileSet_.at(tile.TileSet),screen_,&TileRect);
	      };
	  };	 
      };
};
void TBFE_Render::renderActors()
{
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      TBFE_Base::ActorList.at(i)->runAction();
    };
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      Position ActorPosition=TBFE_Base::ActorList.at(i)->getPosition();
      Position CurrentPosition=TBFE_Base::MainPlayer->getPosition();
      Actor * currentActor=TBFE_Base::ActorList.at(i);
      SDL_Rect Frame;
      Action action=currentActor->getCurrentAction();
      Frame=currentActor->getCollisionRect();
      int x=ActorPosition.X-(CurrentPosition.X-offset_.X);
      int y=ActorPosition.Y-(CurrentPosition.Y-offset_.Y);
      applyImage(x,y, currentActor->getCollisionMap(),screen_,&Frame);
      for (int Layer=0;Layer<action.getLayerSize();Layer++)
	{
	  Animation * animation=action.getLayer(Layer);
	  Frame=action.getFrameRect(Layer);
	  if (animation->getSheet()!=NULL)
	    {
	      applyImage(x+animation->getOffset().X,
			 y-sqrt(pow(animation->getOffset().Y,2)+
				pow(ActorPosition.Z,2)), 
			 animation->getSheet(),screen_,&Frame);
	    };
	};
      if (currentActor->getWalking())
	{
	  currentActor->setWalking(false);
	}
      else if (action.getName()=="Walk")
	{
	  currentActor->endCurrentAction();
	};
    };
};
void TBFE_Render::renderWindowList()
{
  SDL_Rect NewWindow;
  for (int i=0;i<TBFE_Base::WindowList.size();i++)
    {
      Window * window=TBFE_Base::WindowList.at(i);
      if (window->getVisibility())
	{
	  Position windowPosition=window->getScreenPosition();
	  NewWindow.x=0;
	  NewWindow.y=0;
	  NewWindow.w=window->getDimensions().X;
	  NewWindow.h=window->getDimensions().Y;	
	  if (window->getShowBackground())
	    {
	      applyImage(windowPosition.X,windowPosition.Y,window_,screen_,&NewWindow);
	    };
	  window->renderElements(screen_);
	};
    };
};
bool TBFE_Render::addTileSet(string source)
{
  SDL_Surface * newTileSet=TBFE_Base::CheckSheets(source);
  if (newTileSet!=NULL)
    {
      tileSet_.push_back(newTileSet);
      return true;
    };
  return false;
};
