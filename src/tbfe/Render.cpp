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
  glEnable(GL_LIGHT0);
  GLfloat specular[3];
  specular[0]=0.3f;
  specular[1]=0.3f;
  specular[2]=0.3f;
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,specular);
  specular[0]=0.0f;
  specular[1]=0.0f;
  specular[2]=0.0f;
  glLightfv(GL_LIGHT0,GL_AMBIENT,specular);
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
  screen_=SDL_SetVideoMode(TBFE_Base::ScreenDimensions.X,TBFE_Base::ScreenDimensions.Y,32,SDL_OPENGL | SDL_FULLSCREEN );
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
  refreshMapLayer(0);
};
void TBFE_Render::finalRender(bool doFlip)
{  
  if (TBFE_Base::CurrentMap.checkChanged())
    {
      TBFE_Base::CurrentMap.setChanged(false);
      refreshMapLayer(0);
    };
  Position mapDimensions=TBFE_Base::CurrentMap.getDimensions();
  lightPosition_[0]=0.0f;
  lightPosition_[1]=1.0f;
  lightPosition_[2]=0.0f;
  lightPosition_[3]=1.0f;
  glLoadIdentity();
  glLightfv(GL_LIGHT0,GL_POSITION,lightPosition_);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  PositionF cameraOffset=TBFE_Base::getCameraOffset();
  PositionF cameraFollowOffset=TBFE_Base::getCameraFollowOffset();
  PositionF cameraAngle=TBFE_Base::getCameraAngle();
  glTranslatef(cameraFollowOffset.X,cameraFollowOffset.Y,cameraFollowOffset.Z);
 
  glRotatef(cameraAngle.X,1,0,0);
  glRotatef(cameraAngle.Y,0,1,0);
  glRotatef(cameraAngle.Z,0,0,1);
  glTranslatef(cameraOffset.X,cameraOffset.Y,cameraOffset.Z);
  //glRotatef(-TBFE_Base::MainPlayer->getRotationF().Y,0,1,0);
  glTranslatef(-TBFE_Base::MainPlayer->getPositionF().X/20,0,-TBFE_Base::MainPlayer->getPositionF().Z/20);
  renderActors();
  renderMapLayer(0,0,0);
  renderWindowList();
  SDL_GL_SwapBuffers();
  TBFE_Base::DeleteTempSheets();
  int Error=glGetError();
  if(Error != GL_NO_ERROR )
    {
      stringstream errorString;
      errorString << "OpenGl eror:" << hex << Error << dec;
      TBFE_Base::MainConsole.write(errorString.str());
    }
};
void TBFE_Render::refreshMapLayer(int Layer)
{
  TBFE_Base::MainConsole.write("Map refreshed");
  map_.indices.clear();
  map_.vertices.clear();
  map_.texCoords.clear();
  map_.normals.clear();
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
	      map_.normals.push_back(0);
	      map_.normals.push_back(1);
	      map_.normals.push_back(0);
	    };
	  //bottom Right
	  aiVector3D newCoord;
	  GLfloat vertex[]={tileSize*mapX,0,tileSize*mapY};
	  map_.vertices.push_back(vertex[0]);
	  map_.vertices.push_back(vertex[1]);
	  map_.vertices.push_back(vertex[2]);
	  newCoord.x=start.X;
	  newCoord.y=start.Y;
	  map_.texCoords.push_back(newCoord);
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
	  map_.vertices.push_back(vertex[0]); 
	  map_.vertices.push_back(vertex[1]); 
	  map_.vertices.push_back(vertex[2]);
	  newCoord.x=start.X+end.X;
	  newCoord.y=start.Y;
	  map_.texCoords.push_back(newCoord);
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
	  map_.vertices.push_back(vertex[0]); 
	  map_.vertices.push_back(vertex[1]); 
	  map_.vertices.push_back(vertex[2]);
	  newCoord.x=start.X+end.X;
	  newCoord.y=start.Y+end.Y;
	  map_.texCoords.push_back(newCoord);
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
	  map_.vertices.push_back(vertex[0]); 
	  map_.vertices.push_back(vertex[1]); 
	  map_.vertices.push_back(vertex[2]);
	  newCoord.x=start.X;
	  newCoord.y=start.Y+end.Y;
	  map_.texCoords.push_back(newCoord);
	};
    };
  for (int i=0;i<dimensions.X*dimensions.Y*4;i++)
    {
      map_.indices.push_back(i);
    };  
};
int TBFE_Render::renderMapLayer(int x,int y, int Layer)
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glBindTexture(GL_TEXTURE_2D,tileSet_.at(0).texture);
  glVertexPointer(3,GL_FLOAT,0,&map_.vertices[0]);
  glNormalPointer(GL_FLOAT,0,&map_.normals[0]);
  glTexCoordPointer(3,GL_FLOAT,sizeof(aiVector3D),&map_.texCoords[0]);
  GLfloat color[]={1.0f,1.0f,1.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
  glDrawElements(GL_QUADS,map_.indices.size(),GL_UNSIGNED_INT,&map_.indices[0]);
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
      PositionF ActorPosition=TBFE_Base::ActorList.at(i)->getPositionF();
      PositionF rotation=TBFE_Base::ActorList.at(i)->getRotationF();
      Position CurrentPosition=TBFE_Base::MainPlayer->getPosition();
      Actor * currentActor=TBFE_Base::ActorList.at(i);
      SDL_Rect Frame;
      Action action=currentActor->getCurrentAction();
      //Frame=currentActor->getCollisionRect();
      for (int Layer=0;Layer<action.getLayerSize();Layer++)
	{
	  Animation * animation=action.getLayer(Layer);
	  ModelData * model;
	  PositionF layerOffset=animation->getOffset();
	  PositionF layerRotation=animation->getRotation();
	  
	  model=animation->getModel();
	  if (animation->getModel()!=NULL)
	    {
	      aiVector3D tposition(ActorPosition.X/20+layerOffset.X,ActorPosition.Y/20+layerOffset.Y,ActorPosition.Z/20+layerOffset.Z);
	      aiVector3D trotation(rotation.X+layerRotation.X,rotation.Y+layerRotation.Y,rotation.Z+layerRotation.Z);
	      aiVector3D tscale(0,0,0);
	      drawNodes(model,tposition,trotation,tscale);
	    };
	  if (TBFE_Base::showCollision)
	    {
	      glPushMatrix();
	      glTranslatef(ActorPosition.X/20,ActorPosition.Y/20,ActorPosition.Z/20);
	      PositionF dimensions;
	      PositionF offset;
	      for (int i=0;i<currentActor->getNumCollisionBox();i++)
		{
		  CollisionBox actorCollision=*currentActor->getCollisionBox(i);
		  dimensions=actorCollision.getDimensions();
		  offset=actorCollision.getPosition();
		  actorCollision.setRotation(rotation.X,-rotation.Y,rotation.Z);   
		  vector<PositionF> points=actorCollision.generatePoints(actorCollision.getPosition(),actorCollision.getDimensions());
		  glDisable(GL_CULL_FACE);
		  glEnableClientState(GL_VERTEX_ARRAY);
		  glVertexPointer(3,GL_FLOAT,0,&points[0]);
		  GLuint indices[24]={0,1,2,3,
				      0,1,5,4,
				      2,3,7,6,
				      1,2,6,5,
				      3,0,4,7,
				      4,5,6,7};
		  glDrawElements(GL_QUADS,24,GL_UNSIGNED_INT,&indices);
		  glDisableClientState(GL_VERTEX_ARRAY);
		  glEnable(GL_CULL_FACE);
		};
	      glPopMatrix();
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
	  SDL_Surface * windowSurface=window->renderElements(screen_);
	  if (windowSurface!=NULL)
	    {
	      applyImage(windowPosition.X,windowPosition.Y,windowSurface,NULL);
	    };
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
