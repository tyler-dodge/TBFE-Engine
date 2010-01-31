#include "MapEditor.h"
MapEditor::MapEditor()
{
  Layer=0;
  Text=NULL;
  Cursor.X=0;
  Cursor.Y=0;
  MapX=0;
  MapY=0;
  ShowCollision=true;
  OffsetY=0;
  Passability=0;
  SDL_ShowCursor(0);
  NewType=DIRT;
  CurrentSet=1;
  ChangeMap("Maps/Station.fmm");
  LoadActors("ActorTypes.cfg");
  Panel=LoadImage("Images/UI/VertPanel.png");
  SelectSquare=LoadImage("Images/UI/SelectSquare.png");
  SDL_SetColorKey(SelectSquare,SDL_SRCCOLORKEY,SDL_MapRGB(SelectSquare->format,255,255,255));
};
MapEditor::~MapEditor()
{
  if (Panel!=NULL)
    {
      SDL_FreeSurface(Panel);
    };
  if (SelectSquare!=NULL)
    {
      SDL_FreeSurface(SelectSquare);
    };
  if(Text!=NULL)
    {
      SDL_FreeSurface(Text);
    };
};
string MapEditor::TextInput()
{
  bool EndLoop=false;
  string CurrentString;
  int StringLength;
  TBFE_Base::MainConsole.ShowConsole=true;
  while (!EndLoop)
    {
      TBFE_Base::MainConsole.ShowConsole=true;
      RunEngine();
      if (TBFE_Base::MainConsole.CurrentLine[0]==(char)0 && CurrentString!="")
	{
	  CurrentString=TBFE_Base::MainConsole.Lines[TBFE_Base::MainConsole.NumberOfLines-1];
	  EndLoop=true;
	}
      else
	{
	  CurrentString=(string)TBFE_Base::MainConsole.CurrentLine;
	};
    };
  TBFE_Base::MainConsole.ShowConsole=false;
  return CurrentString;
};
Direction MapEditor::EditorLoop ()
{
  if (TBFE_Base::MainConsole.ShowConsole==true)
    {
      RunEngine();
      return NORMAL;
    };
  while(SDL_PollEvent(&Logic.event))
    {
      TBFE_Base::ActorList.resize(0);
      if (Logic.event.type==SDL_KEYDOWN)
	    {
	  
	  if ((int)Logic.event.key.keysym.sym==96 && KeysDown[(int)Logic.event.key.keysym.sym]==false)
	    {
	      TBFE_Base::MainConsole.ShowConsole=true;
	      Logic.KeysDown[(int)Logic.event.key.keysym.sym]=true;
	      
	    };
	  switch(Logic.event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      return QUIT;
	      break;
	    case SDLK_F1:
	      if (!KeysDown[(int)Logic.event.key.keysym.sym])
		{
		  TBFE_Base::CurrentMap.DumpMap(TextInput());
		};
	      break;
	    case SDLK_F2:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  if (ShowCollision)
		    {
		      ShowCollision=false;
		    }
		  else
		    {
		      ShowCollision=true;
		    };
		};
	      break;
	    case SDLK_F4:
	      if (!KeysDown[(int)Logic.event.key.keysym.sym])
		{
		  string Integer;
		  int NewNumber1;
		  int NewNumber2;
		  NewNumber1=atoi(Integer.c_str());
		  NewNumber2=atoi(Integer.c_str());
		  TBFE_Base::CurrentMap.GenerateMap(NewNumber1,NewNumber2,false);
		};
	      break;
	    case SDLK_F5:
	      if (!KeysDown[(int)Logic.event.key.keysym.sym])
		{
		  RenderWindow.ShowForeground=false;
		};
	      break;
	    case SDLK_p:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  NewType=(TileType)(NewType-1);
		};
	      break;
	    case SDLK_l:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  NewType=(TileType)(NewType+1);
		};
	      break;
	    case SDLK_UP:
	      if (!KeysDown[(int)Logic.event.key.keysym.sym])
		{
		  MapY-=TBFE_Base::TileSize;
		};
	      break;
	    case SDLK_LEFT:
	      if (!KeysDown[(int)Logic.event.key.keysym.sym])
		{
		  MapX-=TBFE_Base::TileSize;
		};
	      break;
	    case SDLK_RIGHT:
	      if (!KeysDown[(int)Logic.event.key.keysym.sym])
		{
		  MapX+=TBFE_Base::TileSize;
		};
	      break;
	    case SDLK_DOWN:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  MapY+=TBFE_Base::TileSize;
		};
	      break;
	      //Switch Tilesets
	    case SDLK_q:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  CurrentSet-=1;
		  if (CurrentSet<0)
		    {
		      CurrentSet=RenderWindow.TileSet.size()-1;
		    };
		};
	      break;
	    case SDLK_a:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  CurrentSet+=1;
		  if (CurrentSet>=RenderWindow.TileSet.size())
		    {
		      CurrentSet=0;
		    };
		};
	      break;
	      //Move Up TileSet List
	    case SDLK_w:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  OffsetY-=TBFE_Base::TileSize;
		};
	      break;
	      //Move Down Tilest List
	    case SDLK_s:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  OffsetY+=TBFE_Base::TileSize;
		};
	      break;
	      //Change Passability cursor to 255
	    case SDLK_e:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  Passability=255;
		};
	      break;
	      //Change Passability cursor to 0
	    case SDLK_d:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  Passability=0;
		};
	      break;
	    case SDLK_1:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  Layer=0;
		};
	      break;
	    case SDLK_2:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  Layer=1;
		};
	      break;
	    case SDLK_3:
	      if (KeysDown[(int)Logic.event.key.keysym.sym]==false)
		{
		  Layer=2;
		};
	      break;
	    case SDLK_RETURN:
	      if (Logic.event.button.x/TBFE_Base::TileSize>1)
		{
		  TBFE_Base::CurrentMap.ChangeTile((Cursor.X+MapX)/TBFE_Base::TileSize,
					(Cursor.Y+MapY)/TBFE_Base::TileSize,NewType,
					CurrentSet,Passability,Layer);
		};
	      break;
	    };
	  KeysDown[(int)Logic.event.key.keysym.sym]=true;
	};
      if (Logic.event.type==SDL_KEYUP)
	{
	  KeysDown[(int)Logic.event.key.keysym.sym]=false;
	};
      if (Logic.event.type==SDL_MOUSEBUTTONDOWN)
	{
	  int x = Logic.event.button.x+MapX;
	  int y = Logic.event.button.y+MapY;
	  if (Logic.event.button.button==SDL_BUTTON_LEFT)
	    {
	      if (Logic.event.button.x/TBFE_Base::TileSize>1)
		{
		  TBFE_Base::CurrentMap.ChangeTile(x/TBFE_Base::TileSize,
					       y/TBFE_Base::TileSize,
					       NewType,CurrentSet,Passability,Layer);
		}
	      else
		{
		  NewType=(TileType)(Logic.event.button.x/TBFE_Base::TileSize+
				    (OffsetY/TBFE_Base::TileSize + Logic.event.button.y/TBFE_Base::TileSize)*2);
		};
	    };
	  if (Logic.event.button.button==SDL_BUTTON_RIGHT)
	    {
	      NewType=TBFE_Base::CurrentMap.GetTile(x/TBFE_Base::TileSize,y/TBFE_Base::TileSize).Type;
	    };
	};
      if (Logic.event.type==SDL_MOUSEMOTION)
	{
	  Cursor.X=(Logic.event.motion.x/TBFE_Base::TileSize)*TBFE_Base::TileSize;
	  Cursor.Y=(Logic.event.motion.y/TBFE_Base::TileSize)*TBFE_Base::TileSize;
	};
    };
    RenderWindow.RenderMap(MapX,MapY,ShowCollision);
    RenderWindow.RenderForeground(MapX,MapY,false);
    RenderWindow.RenderWindowList();
    ApplyImage(0,0,Panel,RenderWindow.screen);
    ApplyImage(0,-OffsetY,RenderWindow.TileSet[CurrentSet],RenderWindow.screen);
    //3 0
    //4 1
    //3/2*2
    ApplyImage((NewType-(int)(NewType/2)*2)*TBFE_Base::TileSize,
	       (int)(NewType/2)*TBFE_Base::TileSize-OffsetY,SelectSquare,RenderWindow.screen);
    ApplyImage(Cursor.X,Cursor.Y,SelectSquare,RenderWindow.screen);
    SDL_Rect PanelRect;
    PanelRect.x=0;
    PanelRect.y=0;
    PanelRect.w=RenderWindow.SCREEN_WIDTH;
    PanelRect.h=50;
    SDL_Flip(RenderWindow.screen);
    return NORMAL;
};
