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
	  TBFE_Base::MainPlayer->changePosition(0);
	}
      if (keysDown_['s'])
	{
	  TBFE_Base::MainPlayer->changePosition(180.0f);
	}
      if (keysDown_['d'])
	{
	  TBFE_Base::MainPlayer->changePosition(-90.0f);
	}
      if (keysDown_['a'])
	{
	  TBFE_Base::MainPlayer->changePosition(90.0f);
	};
      if (keysDown_['q'])
	{
	  TBFE_Base::MainPlayer->rotate(Quaternion(0,1,0,5));
	};
      if (keysDown_['e'])
	{
	  TBFE_Base::MainPlayer->rotate(Quaternion(0,1,0,-5));
	};
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
