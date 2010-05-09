#include "Logic.h"
TBFE_Logic::TBFE_Logic()
{
  for (int i=0;i<311;i++)
    {
      keysDown_[i]=false;
    };
};
TBFE_Logic::~TBFE_Logic()
{
};

int TBFE_Logic::checkTalker()
{
  //DEPRECATED
};
void TBFE_Logic::playerMovement()
{
  //PlayerMovement
  bool PlayerMoved=true;  
  int PlayerNumber=TBFE_Base::GetActorNum(TBFE_Base::MainPlayer);
  if (TBFE_Base::MainPlayer->getCurrentAction().getName()=="Walk" ||
      TBFE_Base::MainPlayer->getCurrentAction().getName()=="None")
    {
      if (keysDown_['w'])
	{
	  TBFE_Base::MainPlayer->changePosition(TBFE_Base::MainPlayer->getRotationF().Y,false);
	}
      if (keysDown_['s'])
	{
	  TBFE_Base::MainPlayer->changePosition(180.0f+TBFE_Base::MainPlayer->getRotationF().Y,false);
	}
      if (keysDown_['d'])
	{
	  TBFE_Base::MainPlayer->changePosition(TBFE_Base::MainPlayer->getRotationF().Y+270.0f,false);
	}
      if (keysDown_['a'])
	{
	  TBFE_Base::MainPlayer->changePosition(TBFE_Base::MainPlayer->getRotationF().Y+90.0f,false);
	;}
      if (keysDown_['q'])
	{
	  PositionF rotation=TBFE_Base::MainPlayer->getRotationF();
	  rotation.Y+=5;
	  TBFE_Base::MainPlayer->setRotationF(rotation.X,rotation.Y,rotation.Z);
	};
      if (keysDown_['e'])
	{
	  PositionF rotation=TBFE_Base::MainPlayer->getRotationF();
	  rotation.Y-=5;
	  TBFE_Base::MainPlayer->setRotationF(rotation.X,rotation.Y,rotation.Z);
	};
    };
};
int TBFE_Logic::contextAction()
{
  int NPC_Exists=checkTalker();
  Tile HarvestTile;
  Position playerPosition;
  playerPosition.X=(TBFE_Base::MainPlayer->getPosition().X+TBFE_Base::TileSize/2)/TBFE_Base::TileSize+TBFE_Base::MainPlayer->getDirOffset().X;
  playerPosition.Y=(TBFE_Base::MainPlayer->getPosition().Y+TBFE_Base::TileSize/2)/TBFE_Base::TileSize+TBFE_Base::MainPlayer->getDirOffset().Y;
  
  if (NPC_Exists!=-1)
    {
      TBFE_Base::Talker=TBFE_Base::ActorList[NPC_Exists];
      if (TBFE_Base::Talker->getMobile())
	{
	  PositionF newAngle=TBFE_Base::MainPlayer->getRotationF();
	  newAngle.Z=360-newAngle.Z;
	  TBFE_Base::Talker->setRotationF(newAngle.X,newAngle.Y,newAngle.Z);
	};
      TBFE_Base::Talker->getConversation(false);
      stringstream ActorSelf;
      ActorSelf << "Caller=" << "engine.Logic:GetActor(" << NPC_Exists << ")";
      TBFE_Base::MainConsole.runLine(ActorSelf.str());
      //Talk to Actor
      return 1;
    }
  else
    {
      //Use Tool
      return 2;
    };
};

char TBFE_Logic::textInput(int KeyPress,bool ShiftDown)
{
  char Letter=0;
  //Text check
  if (
      (KeyPress>=(char)97 && KeyPress<=(char)122 ||
       KeyPress==SDLK_PERIOD) ||
      (KeyPress>=(char)40 && KeyPress<=(char)63) ||
      KeyPress==32 || KeyPress==39
      )
    {
      if (ShiftDown==true && 
	  KeyPress>=(char)97 && KeyPress<=(char)122)
	{
	  Letter=(char)(KeyPress-32);
	}
      else if (ShiftDown==true && 
	       KeyPress>=(char)39 && KeyPress<=(char)61)
	{
	  switch(KeyPress)
	    {
	    case 39:
	      Letter='"';
	      break;
	    case 45:
	      Letter='_';
	      break;
	    case 48:
	      Letter=')';
	      break;
	    case 49:
	      Letter='!';
	      break;
	    case 50:
	      Letter='@';
	      break;
	    case 51:
	      Letter='#';
	      break;
	    case 52:
	      Letter='$';
	      break;
	    case 53:
	      Letter='%';
	      break;
	    case 54:
	      Letter='^';
	      break;
	    case 55:
	      Letter='&';
	      break;
	    case 56:
	      Letter='*';
	      break;
	    case 57:
	      Letter='(';
	      break;
	    case 59:
	      Letter=':';
	      break;
	    case 61:
	      Letter='+';
	      break;
	    default:
	      Letter=KeyPress;
	      break;
	    };
	}		       
      else
	{
	  Letter=(char)KeyPress;
	};
    };
  if (KeyPress==8)
    {
      Letter=(char)1;
    };
  return Letter;
};
bool TBFE_Logic::pollEvent()
{
  newEvent_=SDL_PollEvent(&event_);
  if (newEvent_)
    {
      if (event_.type==SDL_KEYDOWN)
	{
	  setKeyDown(event_.key.keysym.sym,true);
	};
      if (event_.type==SDL_KEYUP)
	{
	  setKeyDown(event_.key.keysym.sym,false);
	};
    };
  return newEvent_;
};
bool TBFE_Logic::isEventNew()
{
  return newEvent_;
};
SDL_Event TBFE_Logic::getEvent()
{
  return event_;
};
bool TBFE_Logic::checkKeyDown(int key)
{
  if (key>316)
    {
      return false;
    };
  return keysDown_[key];
};
void TBFE_Logic::setKeyDown(int key,bool newSetting)
{
  if (key>316)
    {
      return;
    };
  keysDown_[key]=newSetting;
};
