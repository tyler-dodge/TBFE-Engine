#include "Main.h"
TBFE::TBFE()
{
  TBFE_Base::ActorList.resize(0);
  frame_=0;
  TBFE_Base::KeyControl=true;
  time_=600;
  frameRate_.Start();
  quit_=false;
  TBFE_Base::MainPlayer=createActor(1000,1000,"Player","Npc");
  addActor(TBFE_Base::MainPlayer);
  SDL_GetMouseState(&mousePosition_.X,&mousePosition_.Y);
  mouseMovement_.X=mousePosition_.X;
  mouseMovement_.Y=mousePosition_.Y;
  return;
};
TBFE::~TBFE()
{
  deleteWindowList();
  deleteCreatedActorList();
  TBFE_Base::DeleteAnimationSheets();
};
bool TBFE::createFile(string name)
{  
  ofstream NewFile(name.c_str(),ofstream::binary);
  return true;
};
PositionF TBFE::getCameraAngle()
{
  return renderWindow_.getCameraAngle();
};
void TBFE::setCameraAngle(float x,float y,float z)
{
  renderWindow_.setCameraAngle(x,y,z);
};
void TBFE::addEvent(std::string Target,Element * element,Window * Parent,std::string Function,Event TargetEvent)
{
  EventType NewEvent;
  NewEvent.TargetName=Target;
  NewEvent.TargetElement=element;
  NewEvent.Parent=Parent;
  NewEvent.TargetEvent=TargetEvent;
  NewEvent.Function=Function;
  NewEvent.Enabled=true;
  if (NewEvent.TargetElement==NULL)
    {
      TBFE_Base::MainConsole.write("Element does not exist");
      return;
    }
  else if (NewEvent.Parent==NULL)
    {
      TBFE_Base::MainConsole.write("Parent Window does not exist");
      return;
    };
  eventList_.push_back(NewEvent);
};
void TBFE::addGlobalEvent(std::string Target,Event TargetEvent, int Key,std::string Function)
{
  EventType NewEvent;
  NewEvent.TargetName=Target;
  NewEvent.TargetElement=NULL;
  NewEvent.Parent=NULL;
  NewEvent.TargetEvent=TargetEvent;
  NewEvent.Function=Function;
  NewEvent.Key=Key;
  NewEvent.Enabled=true;
  eventList_.push_back(NewEvent);
};
bool TBFE::addTileSet(std::string Source)
{
  
  if (renderWindow_.addTileSet("Images/TileSets/"+Source))
    {
      TBFE_Base::MainConsole.write("    File Does not exist");
      return false;
    };
  TBFE_Base::CurrentMap.addTileSet(Source);  
};
EventType * TBFE::selectEvent(std::string Name)
{
  for(int i=0;i<eventList_.size();i++)
    {
      if (eventList_.at(i).TargetName==Name)
	{
	  return &eventList_.at(i);
	};
    };
};
void TBFE::initMap()
{
  renderWindow_.initializeTileSets();
};
void TBFE::changeMap(std::string MapName)
{
  TBFE_Base::ActorList.resize(0);
  deleteCreatedActorList(false);
  TBFE_Base::CurrentMap.loadMap(MapName);
  addActor(TBFE_Base::MainPlayer);
};
void TBFE::addActor(Actor *NewActor)
{
  if (NewActor!=NULL)
    {
      TBFE_Base::ActorList.push_back(NewActor);
    }
  else
    {
      TBFE_Base::MainConsole.write("   Actor is equal to NULL");
    };
};
bool TBFE::removeActor(Actor *actorPtr)
{
  int actor=TBFE_Base::GetActorNum(actorPtr);
  if (actor!=-1 || TBFE_Base::ActorList.size()>actor)
    {
      TBFE_Base::ActorList.erase(TBFE_Base::ActorList.begin()+actor);
      return true;
    };
  return false;
};
void TBFE::addWindow(Window *NewWindow)
{
  if (NewWindow!=NULL)
    {
      TBFE_Base::WindowList.push_back(NewWindow);
    }
  else
    {
      TBFE_Base::MainConsole.write("   Window is equal to NULL");
    };
};
void TBFE::addBuilding(Building newBuilding)
{
  for (int i=0;i<newBuilding.getNumberOfWalls();i++)
    {
      addActor(newBuilding.getWall(i));
    };
  Position floorDimensions=newBuilding.getFloorDimensions();
  Position roofDimensions=newBuilding.getRoofDimensions();
  Position buildingPosition=newBuilding.getPosition();
  for (int y=0;y<floorDimensions.Y;y++)
    {
      for (int x=0;x<floorDimensions.X;x++)
	{
	  Tile newTile=newBuilding.getFloorTile(x,y);
	  if (newTile.Type!=-1)
	    {
	      TBFE_Base::CurrentMap.changeTile(buildingPosition.X+x,
					       buildingPosition.Y+y,newTile,0);
	    }
	};
    };
  for (int y=0;y<roofDimensions.Y;y++)
    {
      for (int x=0;x<roofDimensions.X;x++)
	{
	  Tile newTile=newBuilding.getRoofTile(x,y);
	  if (newTile.Type!=-1)
	    {
	      TBFE_Base::CurrentMap.changeTile(buildingPosition.X+x,
					       buildingPosition.Y+y-2,newTile,1);
	    }
	};
    };
};
void TBFE::checkEvents()
{
  int mouseState=SDL_GetMouseState(&mousePosition_.X,&mousePosition_.Y);
  for(int i=0;i<eventList_.size();i++)
    {
      EventType currentEvent=eventList_.at(i);
      if (currentEvent.Enabled)
	{
	  Position eventPosition;
	  Position screenPosition;
	  Position elementDimensions;
	  if (currentEvent.TargetElement!=NULL)
	    {
	      eventPosition=currentEvent.TargetElement->getPosition();
	    };
	  if (currentEvent.Parent!=NULL)
	    {
	      screenPosition=currentEvent.Parent->getScreenPosition();
	    };
	  if (currentEvent.TargetElement!=NULL)
	    {
	      elementDimensions=currentEvent.TargetElement->getDimensions();
	    };
	  switch(currentEvent.TargetEvent)
	    {
	    case CLICK:
	      if (mousePosition_.X>eventPosition.X+screenPosition.X 
		  && mousePosition_.Y>eventPosition.Y+
		  screenPosition.Y
		  && mousePosition_.X<elementDimensions.X+
		  eventPosition.X+screenPosition.X
		  && mousePosition_.Y<elementDimensions.Y+
		  eventPosition.Y+screenPosition.Y
		  && currentEvent.Enabled 
		  && currentEvent.Parent->getVisibility()
		  && mouseState==1 && mouseDown_==false
		  )
		{
		  stringstream windowString;
		  windowString << "elementTarget=Tbfe.getWindowByNum(" << TBFE_Base::getWindowNum(currentEvent.Parent) << ")";
		  TBFE_Base::MainConsole.runLine(windowString.str().c_str());
		  TBFE_Base::MainConsole.runLine(currentEvent.Function.c_str());
		};
	      break;
	    case MOUSEMOVE:
	      if ((mouseMovement_.X!=mousePosition_.X || mouseMovement_.Y!=mousePosition_.Y) &&
		  currentEvent.Enabled==true && currentEvent.Parent==NULL && currentEvent.TargetElement==NULL)
		{
		  stringstream writeMouse;
		  writeMouse << "mouseMovement=Misc.PositionF();mouseMovement.X=";
		  writeMouse << -mouseMovement_.X+mousePosition_.X << ";mouseMovement.Y=";
		  writeMouse << -mouseMovement_.Y+mousePosition_.Y << ";";
		  TBFE_Base::MainConsole.runLine(writeMouse.str());
		  TBFE_Base::MainConsole.runLine(currentEvent.Function.c_str());
		  mouseMovement_.X=mousePosition_.X;
		  mouseMovement_.Y=mousePosition_.Y;
		};
	      if (currentEvent.Parent!=NULL && currentEvent.TargetElement!=NULL)
		{
		  if (
		      (mousePosition_.X>eventPosition.X+screenPosition.X 
		       && mousePosition_.Y>eventPosition.Y+
		       screenPosition.Y
		       && mousePosition_.X<elementDimensions.X+
		       eventPosition.X+screenPosition.X
		       && mousePosition_.Y<elementDimensions.Y+
		       eventPosition.Y+screenPosition.Y
		       && currentEvent.Enabled 
		       && currentEvent.Parent->getVisibility()
		       && mouseMovement_.X!=mousePosition_.X && mouseMovement_.Y!=mousePosition_.Y)
		      )
		    {
		      TBFE_Base::MainConsole.runLine(currentEvent.Function.c_str());
		      mouseMovement_.X=mousePosition_.X;
		      mouseMovement_.Y=mousePosition_.Y;
		    };
		};
	      break;
	    case KEYPRESS:
	      SDL_Event currentSdlEvent=logic_.getEvent();
	      if (currentSdlEvent.key.keysym.sym==currentEvent.Key && 
		  logic_.checkKeyDown(currentEvent.Key))
		{
		  TBFE_Base::MainConsole.runLine(currentEvent.Function.c_str());	      
		};
	      break;
	    };
	};
    };
  if (mouseState==1)
    {
      mouseDown_=true;
    }
  else
    {
      mouseDown_=false;
    };
};
Direction TBFE::runEngine()
{
  frame_++;
  while(logic_.pollEvent())
    {
      SDL_Event currentSdlEvent=logic_.getEvent();
      checkEvents();
      //Normal KeyBoard Events
      if (currentSdlEvent.type==SDL_KEYDOWN)
	{	  
	  if (TBFE_Base::KeyTarget!=NULL)
	    {
	      char Letter=logic_.textInput(currentSdlEvent.key.keysym.sym,
					   logic_.checkKeyDown(SDLK_LSHIFT));
	      string text=TBFE_Base::KeyTarget->getProperty("text");
	      if (Letter==1)
		{
		  int Size=text.size();
		  if (Size>1)
		    {
		      text.erase(Size-1);
		    }
		  else
		    {
		      text=" ";
		      text.resize(0);
		    };
		}
	      else if (Letter!=0)
		{
		  text+=(int)Letter;
		};
	      TBFE_Base::KeyTarget->setProperty("text",text);
	      TBFE_Base::KeyTarget->reload();  
	    };
	  if (currentSdlEvent.key.keysym.sym<315 && currentSdlEvent.key.keysym.sym>=0)
	    {
	      logic_.setKeyDown(currentSdlEvent.key.keysym.sym,true);
	    };
	  if (logic_.checkKeyDown(27))
	    {
	      quit_=true;
	    };	      
	};
      if (currentSdlEvent.type==SDL_KEYUP)
	{
	  logic_.setKeyDown(currentSdlEvent.key.keysym.sym,false);
	};
    };
  Position mapDimensions=TBFE_Base::CurrentMap.getDimensions();
  if (TBFE_Base::KeyControl==true)
    {
      logic_.playerMovement();
    };
  Position currentPosition=TBFE_Base::MainPlayer->getPosition();
  if (currentPosition.X<0)
    {
      return LEFT;
    }
  else if (currentPosition.Y<0)
    {
      return UP;
    }
  else if (currentPosition.X>mapDimensions.X*TBFE_Base::TileSize)
    {
      return RIGHT;
    }
  else if (currentPosition.Y>mapDimensions.Y*TBFE_Base::TileSize)
    {
      return DOWN;
    };
  renderWindow_.finalRender(true);  
  
  if (frameRate_.GetTicks() > 1000)
    {
      frameRate_.Start();
      time_++;
      int Minutes=time_-(time_/100)*100;
      if (Minutes>=60)
	{
	  time_+=100-Minutes;
	};
      if (time_>2400)
	{
	  time_=0;
	};
      frame_=0;
      return SECOND;
    };
  TBFE_Base::GameSpeed=60/(frame_*1000/frameRate_.GetTicks());
  if (TBFE_Base::GameSpeed>3)
    {
      TBFE_Base::GameSpeed=3;
    };
  if (quit_==true)
    {
      return QUIT;
    };
  return NORMAL;
};
Position TBFE::getMousePosition()
{
  return mousePosition_;
};
