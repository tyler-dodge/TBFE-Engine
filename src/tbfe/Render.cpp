#include "Render.h"
TBFE_Render::TBFE_Render()
{
  screen_=NULL;
  lightingPercentage_=20;
  TTF_Init();
  init();
  TBFE_Base::font=TTF_OpenFont("Images/UI/font.ttf",12);
  textColor_.r=255;
  textColor_.g=255;
  textColor_.b=255;
  darkness_=TBFE_Base::CheckSheets("Images/Darkness.png");
  changeLighting(10);
  window_=TBFE_Base::CheckSheets("Images/UI/Window.png");
  TBFE_Base::CollisionTile=TBFE_Base::CheckSheets("Tile.png");
  setLightPosition(0,0,0);
};
void TBFE_Render::setLightPosition(float x,float y,float z)
{
  lightPosition_[0]=x;
  lightPosition_[1]=y;
  lightPosition_[2]=z;
};
void TBFE_Render::initGl()
{
  glClearColor( 0, 0, .5, 0 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum(-1,
	    1, 
	    -((double)TBFE_Base::ScreenDimensions.Y/(double)TBFE_Base::ScreenDimensions.X),
	    ((double)TBFE_Base::ScreenDimensions.Y/(double)TBFE_Base::ScreenDimensions.X), 
	     1,100);			
  glMatrixMode( GL_MODELVIEW );
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations
  glLoadIdentity();
  GLfloat global_ambient[]={0.1f,0.1f,0.1f,1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,global_ambient);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  GLfloat specular[3];
  specular[0]=0.3f;
  specular[1]=0.3f;
  specular[2]=0.3f;
  glShadeModel(GL_FLAT);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,specular);
  specular[0]=0.0f;
  specular[1]=0.0f;
  specular[2]=0.0f;
  glLightfv(GL_LIGHT0,GL_AMBIENT,specular);
  glEnable(GL_LIGHT0);
  int Error=glGetError();
  //If there was any errors
  if(Error != GL_NO_ERROR )
    {
      TBFE_Base::MainConsole.write("OpenGl failed to load");
      return;    
    }
  TBFE_Base::MainConsole.write("OpenGl initialized");
};
void TBFE_Render::init()
{
  if (SDL_WasInit(SDL_INIT_EVERYTHING)==0)
    {
      SDL_Init(SDL_INIT_EVERYTHING);
    };
  if (screen_!=NULL)
    {
      SDL_FreeSurface(screen_);
    };
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,8);
  screen_=SDL_SetVideoMode(TBFE_Base::ScreenDimensions.X,TBFE_Base::ScreenDimensions.Y,32,SDL_OPENGL | SDL_FULLSCREEN | SDL_HWSURFACE);
  TBFE_Base::MainConsole.write("SDL initialized");
  initGl();
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
  for(GLuint i=0;i<tileSet_.size();i++)
    {
      glDeleteTextures(1,&i);
    };
  tileSet_.resize(0);
  for (int i=0;i<TBFE_Base::CurrentMap.getNumberOfTileSets();i++)
    {
      string tempString="Images/TileSets/"+TBFE_Base::CurrentMap.getTileSet(i);
      TBFE_Base::MainConsole.write(tempString); 
      SDL_Surface * texture=TBFE_Base::CheckSheets(tempString);
      TileSheet newTileSheet;
      newTileSheet.texture=bindImage(texture);
      newTileSheet.dimensions.X=texture->w;
      newTileSheet.dimensions.Y=texture->h;
      tileSet_.push_back(newTileSheet);
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
  //arrangeActors();
  //renderActors();
  for (int i=1;i<TBFE_Base::CurrentMap.getNumberOfLayers();i++)
    {
      //renderMapLayer(CurrentPosition.X-offset_.X,CurrentPosition.Y-offset_.Y,i);
    };
  SDL_Rect Dark;
  Dark.x=0;
  Dark.y=0;
  Dark.w=TBFE_Base::ScreenDimensions.X;
  Dark.h=TBFE_Base::ScreenDimensions.Y;
  //applyImage(0,0,darkness_,screen_,&Dark);
  if (doFlip && SDL_WasInit(SDL_INIT_VIDEO)!=0)
    {
      //SDL_Flip(screen_);
    };
  lightPosition_[1]=1.0f;
  lightPosition_[0]=0.0f;
  lightPosition_[2]=0.0f;
  lightPosition_[3]=1.0f;
  glLoadIdentity();
  glLightfv(GL_LIGHT0,GL_POSITION,lightPosition_);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(-1,-9,-4);
  glRotatef(-TBFE_Base::MainPlayer->getAngle(),0,1,0);
  glTranslatef(-TBFE_Base::MainPlayer->getPositionD().X/20,0,-TBFE_Base::MainPlayer->getPositionD().Z/20);
  renderActors();
  renderMapLayer(0,0,0);
  renderWindowList();
  SDL_GL_SwapBuffers();
  int Error=glGetError();
  if(Error != GL_NO_ERROR )
    {
      TBFE_Base::MainConsole.write("OpenGl failed to load");
    }
};
int TBFE_Render::renderMapLayer(int x,int y, int Layer)
{
  vector<GLuint> indices;
  vector<GLfloat> vertices;
  vector<GLfloat> colors;
  vector<GLfloat> texCoords;
  vector<GLfloat> normals;
  Position dimensions=TBFE_Base::CurrentMap.getDimensions();
  int tileSize=5;
  for (int mapY=0;mapY<dimensions.Y;mapY++)
    {
      for (int mapX=0;mapX<dimensions.X;mapX++)
	{
	  Tile tile=TBFE_Base::CurrentMap.getTile(mapX,mapY,Layer);
	  Position coordPos;
	  TileSheet currentSheet=tileSet_.at(tile.TileSet);
	  coordPos.X=100*(tile.Type-tile.Type/2*2);
	  coordPos.Y=100*tile.Type/2;
	  PositionF start;
	  start.X=(float)coordPos.X/(float)currentSheet.dimensions.X;
	  start.Y=(float)coordPos.Y/(float)currentSheet.dimensions.Y;
	  PositionF end;
	  end.X=100.0f/(float)currentSheet.dimensions.X;
	  end.Y=100.0f/(float)currentSheet.dimensions.Y;
	  for (int i=0;i<4;i++)
	    {
	      normals.push_back(0);
	      normals.push_back(1);
	      normals.push_back(0);
	    };
	  //bottom Right
	  GLfloat coords[]={start.X,start.Y};
	  GLfloat vertex[]={tileSize*mapX,0,tileSize*mapY};
	  vertices.push_back(vertex[0]);
	  vertices.push_back(vertex[1]);
	  vertices.push_back(vertex[2]);
	  texCoords.push_back(coords[0]);
	  texCoords.push_back(coords[1]);
	  //top right
	  if (mapY==0)
	    {
	      tile=TBFE_Base::CurrentMap.getTile(mapX,mapY,Layer);
	    }
	  else
	    {
	      tile=TBFE_Base::CurrentMap.getTile(mapX,mapY-1,Layer);
	    };
	  vertex[0]=tileSize*mapX;
	  vertex[1]=0;
	  vertex[2]=tileSize*mapY-tileSize;
	  vertices.push_back(vertex[0]); 
	  vertices.push_back(vertex[1]); 
	  vertices.push_back(vertex[2]);
	  coords[0]=start.X+end.X;
	  coords[1]=start.Y;
	  texCoords.push_back(coords[0]);
	  texCoords.push_back(coords[1]);
	  //Top Left
	  if (mapX==0 || mapY==0)
	    {
	      tile=TBFE_Base::CurrentMap.getTile(mapX,mapY,Layer);
	    }
	  else
	    {
	      tile=TBFE_Base::CurrentMap.getTile(mapX-1,mapY-1,Layer);
	    };
	  vertex[0]=tileSize*mapX-tileSize;
	  vertex[1]=0;
	  vertex[2]=tileSize*mapY-tileSize;
	  vertices.push_back(vertex[0]); 
	  vertices.push_back(vertex[1]); 
	  vertices.push_back(vertex[2]);
	  coords[0]=start.X+end.X;
	  coords[1]=start.Y+end.Y;
	  texCoords.push_back(coords[0]);
	  texCoords.push_back(coords[1]);
	  //Bottom Left
	  if (mapX==0)
	    {
	      tile=TBFE_Base::CurrentMap.getTile(mapX,mapY,Layer);
	    }
	  else
	    {
	      tile=TBFE_Base::CurrentMap.getTile(mapX-1,mapY,Layer);
	    };
	  vertex[0]=tileSize*mapX-tileSize;
	  vertex[1]=0;
	  vertex[2]=tileSize*mapY;
	  vertices.push_back(vertex[0]); 
	  vertices.push_back(vertex[1]); 
	  vertices.push_back(vertex[2]);
	  coords[0]=start.X;
	  coords[1]=start.Y+end.Y;
	  texCoords.push_back(coords[0]);
	  texCoords.push_back(coords[1]);
	};
    };
  for (int i=0;i<dimensions.X*dimensions.Y*4;i++)
    {
      indices.push_back(i);
    };
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glBindTexture(GL_TEXTURE_2D,tileSet_.at(0).texture);
  glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
  glNormalPointer(GL_FLOAT,0,&normals[0]);
  glTexCoordPointer(2,GL_FLOAT,0,&texCoords[0]);
  GLfloat color[]={1.0f,1.0f,1.0f};
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
  glDrawElements(GL_QUADS,indices.size(),GL_UNSIGNED_INT,&indices[0]);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisable(GL_TEXTURE_2D);
};
void TBFE_Render::renderActors()
{
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      TBFE_Base::ActorList.at(i)->runAction();
    };
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      PositionD ActorPosition=TBFE_Base::ActorList.at(i)->getPositionD();
      PositionD rotation=TBFE_Base::ActorList.at(i)->getRotationD();
      Position CurrentPosition=TBFE_Base::MainPlayer->getPosition();
      Actor * currentActor=TBFE_Base::ActorList.at(i);
      SDL_Rect Frame;
      Action action=currentActor->getCurrentAction();
      Frame=currentActor->getCollisionRect();
      for (int Layer=0;Layer<action.getLayerSize();Layer++)
	{
	  Animation * animation=action.getLayer(Layer);
	  Frame=action.getFrameRect(Layer);
	  aiScene * model;
	  model=animation->getModel();
	  if (animation->getModel()!=NULL)
	    {
	      aiVector3D tposition(ActorPosition.X/20,ActorPosition.Y/20,ActorPosition.Z/20);
	      aiVector3D trotation(270,0,currentActor->getAngle()+180);
	      aiVector3D tscale(0,0,0);
	      drawNodes(model,model->mRootNode,tposition,trotation,tscale);
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
	  int segmentX=NewWindow.w/window_->w+1;
	  int segmentY=NewWindow.h/window_->h+1;
	  if (window->getShowBackground())
	    {
	      for (int y=0;y<segmentY;y++)
		{
		  for (int x=0;x<segmentX;x++)
		    {
		      NewWindow.w=window->getDimensions().X-x*window_->w;
		      NewWindow.h=window->getDimensions().Y-y*window_->h;
		      if (NewWindow.w>window_->w)
			{
			  NewWindow.w=window_->w;
			};
		      if (NewWindow.h>window_->h)
			{
			  NewWindow.h=window_->h;
			};
		      applyImage(windowPosition.X+x*window_->w,windowPosition.Y+y*window_->h,window_,&NewWindow);
		    };
		};
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
      TileSheet newTileSheet;
      newTileSheet.texture=bindImage(newTileSet);
      newTileSheet.dimensions.X=newTileSet->w;
      newTileSheet.dimensions.Y=newTileSet->h;
      tileSet_.push_back(newTileSheet);
      return true;
    };
  return false;
};
