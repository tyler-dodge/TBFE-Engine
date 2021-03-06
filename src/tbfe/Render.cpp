#include "tbfe/Render.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL.h"
TBFE_Render::TBFE_Render(int dimensionX,int dimensionY):
  dimensions_(dimensionX,dimensionY,0)
{
  init();
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
	    -((double)dimensions_.Y/(double)dimensions_.X),
	    ((double)dimensions_.Y/(double)dimensions_.X), 
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
  GLfloat specular[4];
  specular[3]=0.0f;
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
      CONSOLE_WRITE("OpenGl failed to load");
      return;    
    }
  CONSOLE_WRITE("OpenGl initialized");
};
void TBFE_Render::init()
{
  if (SDL_WasInit(SDL_INIT_EVERYTHING)==0)
    {
      SDL_Init(SDL_INIT_EVERYTHING);
    };
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,8);
  SDL_SetVideoMode(dimensions_.X,dimensions_.Y,32,SDL_OPENGL );
  CONSOLE_WRITE("SDL initialized");
  initGl();
 };
TBFE_Render::~TBFE_Render()
{
  SDL_Quit();
};
void TBFE_Render::initializeTileSets(Map * map)
{
  /*
  //Tile Sets
  CONSOLE_WRITE("TileSets Loaded:");
  for(GLuint i=0;i<tileSet_.size();i++)
    {
      glDeleteTextures(1,&i);
    };
  tileSet_.resize(0);
  for (int i=0;i<map->getNumberOfTileSets();i++)
    {
      string tempString="Images/TileSets/"+map->getTileSet(i);
      CONSOLE_WRITE(tempString);
      //SDL_Surface * texture=TBFE_Base::CheckSheets(tempString);
      TileSheet newTileSheet;
      //newTileSheet.texture=TBFE_Base::GetTexture(texture);
      cout << tempString << '\n';
      //newTileSheet.dimensions.X=texture->w;
      //newTileSheet.dimensions.Y=texture->h;
      //tileSet_.push_back(newTileSheet);
    };
  refreshMapLayer(0);
  */
};
void TBFE_Render::finalRender(bool doFlip)
{  
  //if (TBFE_Base::CurrentMap.checkChanged())
  //  {
  //    TBFE_Base::CurrentMap.setChanged(false);
  //    refreshMapLayer(0);
  //  };
  //Position mapDimensions=TBFE_Base::CurrentMap.getDimensions();
  lightPosition_[0]=0.0f;
  lightPosition_[1]=1.0f;
  lightPosition_[2]=0.0f;
  lightPosition_[3]=1.0f;
  glLoadIdentity();
  glLightfv(GL_LIGHT0,GL_POSITION,lightPosition_);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  ScreenImage image=GET_SCREEN_IMAGE("test.png");
  static int x=0;
  static int y=0;
  image.setPosition(x,y);
  x++;
  y++;
  SDL_GL_SwapBuffers();
  /*PositionF cameraOffset=TBFE_Base::getCameraOffset();
  PositionF cameraFollowOffset=TBFE_Base::getCameraFollowOffset();
  Quaternion cameraAngle=TBFE_Base::getCameraAngle();
  glTranslatef(cameraFollowOffset.X,cameraFollowOffset.Y,cameraFollowOffset.Z);
  glMultMatrixf(cameraAngle.toMatrix().dataPointer());
  glTranslatef(cameraOffset.X,cameraOffset.Y,cameraOffset.Z);
  //glRotatef(-TBFE_Base::MainPlayer->getRotationF().Y,0,1,0);
  PositionF position(TBFE_Base::GetMainPlayer()->getPositionF());
  glTranslatef(-position.X/20,0,-position.Z/20);
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
      CONSOLE_WRITE(errorString.str());
      }*/
};
void TBFE_Render::refreshMapLayer(int Layer)
{
  CONSOLE_WRITE("Map refreshed");
  /*
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
	  coordPos.X=100*(tile.Type-floor(tile.Type/2)*2);
	  coordPos.Y=100*floor(tile.Type/2);
	  PositionF start;
	  start.X=(float)coordPos.X/(float)currentSheet.dimensions.X;
	  start.Y=(float)coordPos.Y/(float)currentSheet.dimensions.Y;
	  PositionF end;
	  end.X=99.0f/(float)currentSheet.dimensions.X;
	  end.Y=99.0f/(float)currentSheet.dimensions.Y;
	  for (int i=0;i<4;i++)
	    {
	      map_.normals.push_back(0);
	      map_.normals.push_back(1);
	      map_.normals.push_back(0);
	    };
	  //bottom Right
	  PositionF newCoord;
	  GLfloat vertex[]={tileSize*mapX,0,tileSize*mapY};
	  map_.vertices.push_back(vertex[0]);
	  map_.vertices.push_back(vertex[1]);
	  map_.vertices.push_back(vertex[2]);
	  newCoord.X=start.X;
	  newCoord.Y=start.Y;
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
	  newCoord.X=start.X+end.X;
	  newCoord.Y=start.Y;
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
	  newCoord.X=start.X+end.X;
	  newCoord.Y=start.Y+end.Y;
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
	  newCoord.X=start.X;
	  newCoord.Y=start.Y+end.Y;
	  map_.texCoords.push_back(newCoord);
	};
    };
  for (int i=0;i<dimensions.X*dimensions.Y*4;i++)
    {
      map_.indices.push_back(i);
    };  
  */
};
int TBFE_Render::renderMapLayer(int x,int y, int Layer)
{
  /*
  if (tileSet_.size()>Layer)
    {
      glEnable(GL_TEXTURE_2D);
      glEnable(GL_CULL_FACE);
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glBindTexture(GL_TEXTURE_2D,tileSet_.at(0).texture);
      glVertexPointer(3,GL_FLOAT,0,&map_.vertices[0]);
      glNormalPointer(GL_FLOAT,0,&map_.normals[0]);
      glTexCoordPointer(3,GL_FLOAT,sizeof(PositionF),&map_.texCoords[0]);
      GLfloat color[]={1.0f,1.0f,1.0f};
      glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
      glDrawElements(GL_QUADS,map_.indices.size(),GL_UNSIGNED_INT,&map_.indices[0]);
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
  glDisable(GL_TEXTURE_2D);
    }
  else
    {
      CONSOLE_WRITE("Tile Set not initialized");
      }
  */
};
void TBFE_Render::renderActors()
{
  /*
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      TBFE_Base::ActorList.at(i)->runAction();
    };
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      PositionF ActorPosition=TBFE_Base::ActorList.at(i)->getPositionF();
      Quaternion rotation=TBFE_Base::ActorList.at(i)->getRotation();
      PositionF CurrentPosition=TBFE_Base::GetMainPlayer()->getPositionF();
      Actor * currentActor=TBFE_Base::ActorList.at(i);
      SDL_Rect Frame;
      Action action=currentActor->getCurrentAction();
      //Frame=currentActor->getCollisionRect();
      for (int Layer=0;Layer<action.getLayerSize();Layer++)
	{
	  Animation * animation=action.getLayer(Layer);
	  ModelData * model;
	  PositionF layerOffset=animation->getOffset();
	  Quaternion layerRotation=animation->getRotation();
	  
	  model=animation->getModel();
	  if (animation->getModel()!=NULL)
	    {
	      PositionF tposition(ActorPosition.X/20+layerOffset.X,ActorPosition.Y/20+layerOffset.Y,ActorPosition.Z/20+layerOffset.Z);
	      PositionF tscale(0,0,0);
	      drawNodes(model,tposition,layerRotation*rotation,tscale);
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
		  rotation.w*=-1;
		  actorCollision.setRotation(rotation);
		  vector<PositionF> points=actorCollision.generatePoints(actorCollision.getPosition(),actorCollision.getDimensions());
		  glEnableClientState(GL_VERTEX_ARRAY);
		  glEnableClientState(GL_NORMAL_ARRAY);
		  glVertexPointer(3,GL_FLOAT,0,&points[0]);
		  GLuint indices[24]={0,3,2,1,
				      0,4,5,1,
				      2,6,7,3,
				      1,5,6,2,
				      3,7,4,0,
				      4,7,6,5};
		  PositionF normals[8];
		  PositionF center=actorCollision.getCenter();
		  for (int i=0;i<6;i++)
		    {
		      Quad face;
		      PositionF iNormal;
		      face.points[0]=points.at(indices[i*4]);
		      face.points[1]=points.at(indices[i*4+1]);
		      face.points[2]=points.at(indices[i*4+2]);
		      face.points[3]=points.at(indices[i*4+3]);
		      iNormal=normalize(face);
		      for (int b=0;b<4;b++)
			{
			  normals[indices[i*4+b]]=addNormals(normals[indices[i*4+b]],iNormal);
			};
		    };
		  glNormalPointer(GL_FLOAT,0,&normals[0]);
		  glShadeModel(GL_SMOOTH);
		  glDrawElements(GL_QUADS,24,GL_UNSIGNED_INT,&indices);
		  glShadeModel(GL_SMOOTH);
		  glDisableClientState(GL_VERTEX_ARRAY);
		  glDisableClientState(GL_NORMAL_ARRAY);
		  glEnable(GL_CULL_FACE);
		};
	      glPopMatrix();
	    };
	};
    };
  */
};
void TBFE_Render::renderWindowList()
{
  /*
  SDL_Rect NewWindow;
  for (int i=0;i<TBFE_Base::WindowList.size();i++)
    {
      Window * window=TBFE_Base::WindowList.at(i);
      if (window->getVisibility())
	{
	  Position windowPosition=window->getScreenPosition();
	  SDL_Surface * windowSurface=window->renderElements();
	  if (windowSurface!=NULL)
	    {
	      applyImage(windowPosition.X,windowPosition.Y,windowSurface,NULL);
	    };
	};
    };
  */
};
bool TBFE_Render::addTileSet(string source)
{
  /*
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
  */
  return false;
};
