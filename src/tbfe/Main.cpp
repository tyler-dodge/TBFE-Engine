#include "tbfe/Main.h"
TBFE::TBFE(int dimensionX,int dimensionY) :
  renderWindow_(dimensionX,dimensionY), frame_(0), quit_(false), keyControl_(false)
{
  frame_=0;
  time_=600;
  frameRate_.Start();
  quit_=false;
  showMouse_=true;
  SDL_GetMouseState(&mousePosition_.X,&mousePosition_.Y);
  mouseMovement_.X=mousePosition_.X;
  mouseMovement_.Y=mousePosition_.Y;
  mouseCenter_.X=dimensionX/2;
  mouseCenter_.Y=dimensionY/2;
};
TBFE::~TBFE()
{
};
PositionI TBFE::getMouseCenter()
{
  return mouseCenter_;
};
void TBFE::setMouseCenter(int x,int y)
{
  mouseCenter_.X=x;
  mouseCenter_.Y=y;
};
bool TBFE::createFile(string name)
{  
  ofstream NewFile(name.c_str(),ofstream::binary);
  return true;
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
      CONSOLE_WRITE("    File Does not exist");
      return false;
    };
  Current_Map.addTileSet(Source);  
};
EventType * TBFE::getEvent(std::string Name)
{
  for(int i=0;i<eventList_.size();i++)
    {
      if (eventList_.at(i).TargetName==Name)
	{
	  return &eventList_.at(i);
	};
    };
  return NULL;
};
void TBFE::initMap()
{ 
};
void TBFE::changeMap(std::string MapName)
{
  actors.resize(0);
  Current_Map.loadMap(MapName);
  addActor(Main_Player);
};
void TBFE::addActor(Actor *NewActor)
{
  if (NewActor!=NULL)
    {
      actors.push_back(NewActor);
    }
  else
    {
      CONSOLE_WRITE("   Actor is equal to NULL");
    };
};
int TBFE::Get_Actor_Num(Actor *actorPtr)
{
  vector<Actor *>::iterator it;
  for (it=actors.begin();it<actors.end();it++)
    {
      if (*it==actorPtr) {
	return it-actors.begin();
      }
    }
}
bool TBFE::removeActor(Actor *actorPtr)
{
  int actor=Get_Actor_Num(actorPtr);
  if (actor!=-1 || actors.size()>actor)
    {
      actors.erase(actors.begin()+actor);
      return true;
    };
  return false;
}
void TBFE::checkEvents()
{
  int mouseState=SDL_GetMouseState(&mousePosition_.X,&mousePosition_.Y);
  SDL_Event currentSdlEvent=logic_.getEvent();
  for(int i=0;i<eventList_.size();i++)
    {
      EventType  * currentEvent=&eventList_.at(i);
      if (currentEvent->Enabled)
	{
	  PositionI eventPosition;
	  PositionI screenPosition;
	  PositionI elementDimensions;
	  switch(currentEvent->TargetEvent)
	    {
	    case KEYPRESS:
	      if (currentSdlEvent.type==SDL_KEYUP && logic_.isEventNew())
		{
		  if (currentSdlEvent.key.keysym.sym==currentEvent->Key)
		    {
		      currentEvent->keyDown=false;
		    };
		};
	      if (currentSdlEvent.type==SDL_KEYDOWN)
		{
		  if (currentSdlEvent.key.keysym.sym==currentEvent->Key && !currentEvent->keyDown)
		    {
		      currentEvent->keyDown=true;
		      Console::Instance()->runLine(currentEvent->Function.c_str());	      
		    };
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
bool TBFE::getShowMouse()
{
  return showMouse_;
};
void TBFE::setShowMouse(bool newState)
{
  showMouse_=newState;
  if (newState)
    {
      SDL_ShowCursor(SDL_ENABLE);
    }
  else
    {
      SDL_ShowCursor(SDL_DISABLE);
    };
};
Direction TBFE::runEngine()
{
  frame_++;
  bool checkOnce=false;
  while(logic_.pollEvent() || !checkOnce)
    {
      SDL_Event currentSdlEvent=logic_.getEvent();
      checkEvents();
      //Normal KeyBoard Events
      if (currentSdlEvent.type==SDL_KEYDOWN && logic_.isEventNew())
	{	  
	  if (logic_.checkKeyDown(27))
	    {
	      quit_=true;
	    };
	};
      checkOnce=true;
    };
  PositionI mapDimensions=Current_Map.getDimensions();
  if (keyControl_==true)
    {
      logic_.playerMovement(Main_Player);
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
      if (!showMouse_ && (mousePosition_.X!=screenDimensions_.X/2 || mousePosition_.Y!=screenDimensions_.Y/2))
	{
	  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	  SDL_WarpMouse(mouseCenter_.X,mouseCenter_.Y);
	  SDL_WM_GrabInput( SDL_GRAB_ON );
	  SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
	};
      return SECOND;
    };
  gameSpeed_=60/(frame_*1000/frameRate_.GetTicks());
  if (gameSpeed_>3)
    {
      gameSpeed_=3;
    };
  if (quit_==true)
    {
      return QUIT;
    };
  return NORMAL;
};
PositionI TBFE::getMousePosition()
{
  return mousePosition_;
};
PositionF TBFE::getCameraPosition()
{
  
  PositionF cameraOffset=camera_.getOffset()*20;
  PositionF cameraFollowOffset=camera_.getFollowOffset()*20;
  Quaternion cameraAngle=camera_.getAngle();
  PositionF tempAngle=(applyRotations(cameraFollowOffset,cameraAngle)+cameraOffset);
  tempAngle=Main_Player->getPositionF()-tempAngle;
  return tempAngle*-1;
};
