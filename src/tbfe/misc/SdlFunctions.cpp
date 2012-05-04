#include "tbfe/misc/SdlFunctions.h"
#include "tbfe/Console.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <math.h>
#include <sstream>

SDL_Surface *loadImage(std::string filename,bool UseA)
{  
  if (SDL_WasInit(SDL_INIT_VIDEO)==0)
    {
      SDL_Init(SDL_INIT_VIDEO);
    };
  SDL_Surface* original=NULL;
  SDL_Surface* newImage=NULL;
  original=IMG_Load(filename.c_str());
  if (original!=NULL)
    {
      if (UseA==true)
	{
	  newImage=SDL_DisplayFormatAlpha(original);
	}
      else
	{
	  newImage=SDL_DisplayFormat(original);
	};
      SDL_FreeSurface(original);
    };
  if (newImage==NULL)
    {
      CONSOLE_WRITE("   "+filename+" did not load correctly");
    };
  return newImage;
};
GLuint bindImage(SDL_Surface * textureSource)
{
  if (textureSource==NULL)
    {
      return 0;
    };
  GLuint texture;
  GLint colors;
  GLenum format;
  colors=textureSource->format->BytesPerPixel;
  if (colors == 4)     // contains an alpha channel
    {
      if (textureSource->format->Rmask == 0x000000ff)
	format = GL_RGBA;
      else
	format = GL_BGRA;
    } else if (colors == 3)     // no alpha channel
    {
      if (textureSource->format->Rmask == 0x000000ff)
	format = GL_RGB;
      else
	format = GL_BGR;
    } 
  else
    {
      CONSOLE_WRITE("texture fail");
    };
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  SDL_LockSurface(textureSource);
  glTexImage2D(GL_TEXTURE_2D,0,colors,textureSource->w,textureSource->h,0,format,
	       GL_UNSIGNED_BYTE,textureSource->pixels);
  SDL_UnlockSurface(textureSource);
  return texture;
};
void applyImage(int x,int y,SDL_Surface* source, SDL_Rect* clip)
{
  if (source==NULL)
    {
      return;
    };
  SDL_Rect offset;
  offset.x=x;
  offset.y=y;
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  {
    glLoadIdentity();
    //TODO:ScreenDimensionsSet
    PositionI screenDimensions;
    glOrtho(0,screenDimensions.X,screenDimensions.Y,0,1,10);
    glMatrixMode(GL_MODELVIEW);
    {
      glPushMatrix();
      glLoadIdentity();
      glTranslatef(x,y,-2);
      PositionI dimensions;
      PositionF start;
      PositionF end;
      if (clip!=NULL)
	{
	  dimensions.X=clip->w;
	  dimensions.Y=clip->h;
	  start.X=(float)clip->x/(float)source->w;
	  start.Y=(float)clip->y/(float)source->h;
	  end.X=(float)clip->w/(float)source->w;
	  end.Y=(float)clip->h/(float)source->h;
	}
      else
	{
	  dimensions.X=source->w;
	  dimensions.Y=source->h;
	  start.X=0;
	  start.Y=0;
	  end.X=1;
	  end.Y=1;
	};
      if (source!=NULL)
	{
	  //TODO: setup texture generation
	  GLuint texture=0;//TBFE_Base::GetTexture(source);
	  glEnable(GL_TEXTURE_2D);
	  glDepthFunc(GL_ALWAYS);
	  if (source->format->BytesPerPixel==4)
	    {
	      glEnable(GL_BLEND);
	      glEnable(GL_ALPHA_TEST);
	      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	      glAlphaFunc(GL_GREATER,0.1f);
	      glColor4f(1.0f,1.0f,1.0f,1.0f);
	    }
	  else
	    {
	      glDisable(GL_BLEND);
	      glDisable(GL_ALPHA_TEST);
	    };
	  glBindTexture(GL_TEXTURE_2D,texture);
	  glDisable(GL_LIGHTING);
	  glBegin(GL_QUADS);
	  glTexCoord2f(start.X,start.Y);glVertex3f(0,0,0);
	  glTexCoord2f(start.X,start.Y+end.Y);glVertex3f(0,dimensions.Y,0);
	  glTexCoord2f(start.X+end.X,start.Y+end.Y);glVertex3f(dimensions.X,dimensions.Y,0);
	  glTexCoord2f(start.X+end.X,start.Y);glVertex3f(dimensions.X,0,0);
	  glEnd();
	  glDisable(GL_ALPHA_TEST);
	  glDisable(GL_BLEND);
	  glDisable(GL_TEXTURE_2D);
	  glEnable(GL_LIGHTING);
	  glDepthFunc(GL_LEQUAL);
	};
      glPopMatrix();
    };
  };
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
};
Uint32 getPixel( SDL_Surface *surface, int x, int y )
{
  if (surface==NULL)
    {
      CONSOLE_WRITE("surface does not exist");
      return -1;
    };
  if (x>surface->w || y>surface->h || x<0 || y<0)
    {
      return -1;
    };
    //Convert the pixels to 32 bit
  Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}
/*void drawNodes(ModelData * model, PositionF position,Quaternion rotation,PositionF scale)
{ 
  glPushMatrix();
  //glTranslatef(position[0],position[1],-position[2]);
  glTranslatef(position.X,position.Y,position.Z);
  glMultMatrixf(rotation.toMatrix().dataPointer());
  for (int i=0;i<model->meshes.size();i++)
    {
      glPushMatrix();
      MeshData * currentMesh=model->meshes.at(i);
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glVertexPointer(3,GL_FLOAT,0,&currentMesh->vertices[0]);
      glNormalPointer(GL_FLOAT,0,&currentMesh->normals[0]);
      glTexCoordPointer(3,GL_FLOAT,sizeof(PositionF),&currentMesh->texCoords[0]);
      glDisable(GL_TEXTURE_2D);
      glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
      glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
      glDrawElements(GL_TRIANGLES,currentMesh->indices.size(),GL_UNSIGNED_INT,&currentMesh->indices[0]);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();
    };
    glPopMatrix(); 
    };*/

float roundDown(float num,int place)
{
  float newNum=floor(num*pow(10.0f,(float)place));
  newNum/=pow(10.0f,(float)place);
  return newNum;
};
PositionF applyRotations(PositionF position,Quaternion rotation)
{
  PositionF newPosition=rotation*position;
  return newPosition;
};
//Radians
float convertToAngle(float x,float y)
{
  x=roundDown(x,5);
  y=roundDown(y,5);
  float addAngle=0;
  if (x==0 && y>0)
    {
      return PI/2;
    }
  else if (x==0 && y<0)
    {
      return 3*PI/2;
    }
  else if (x==0 && y==0)
    {
      return 0;
    };
  float absX=x;
  float absY=y;
  if (x<0)
    {
      absX*=-1;
    };
  if (y<0)
    {
      absY*=-1;
    };
  float angle=atan(absY/absX);
  if (y>=0 && x<0)
    {
      angle=PI-angle;
    }
  else if (y<0 && x<0)
    {
      angle=PI+angle;
    }
  else if (y<0 && x>=0)
    {
      angle=2*PI-angle;
    }
  else
    {
    };
  return angle;
};
PositionF addNormals(PositionF normal1,PositionF normal2)
{
  PositionF normal=normal1+normal2;
  float magnitude=sqrt(pow(normal.X,2)+pow(normal.Y,2)+pow(normal.Z,2));
  return normal/magnitude;
};
PositionF normalize(Quad face)
{
  PositionF vector1=face.points[1]-face.points[0];
  PositionF vector2=face.points[3]-face.points[0];
  PositionF normal(vector1.Y*vector2.Z-vector1.Z*vector2.Y,
		   vector1.Z*vector2.X-vector1.X*vector2.Z, 
		   vector1.X*vector2.Y-vector1.Y*vector2.X);
  float magnitude=sqrt(pow(normal.X,2)+pow(normal.Y,2)+pow(normal.Z,2));
  return normal/magnitude;
};
float absVal(float num)
{
  if (num<0)
    {
      num*=-1;
    };
  return num;
};
PositionF crossProduct(PositionF v1,PositionF v2)
{
  PositionF final;
  final.X=v1.Y*v2.Z-v2.Y*v1.Z;
  final.Y=v1.Z*v2.X-v2.Z*v1.X;
  final.Z=v1.X*v2.Y-v2.X*v1.Y;
  return final;
};
Quaternion getQuaternionXYZ(float x,float y,float z)
{
  x*=DEG_RAD;
  y*=DEG_RAD;
  z*=DEG_RAD;
  Quaternion quatX(1,0,0,x);
  Quaternion quatY(0,1,0,y);
  Quaternion quatZ(0,0,1,z);
  quatX=quatX*quatY*quatZ;
  return quatX;
};
