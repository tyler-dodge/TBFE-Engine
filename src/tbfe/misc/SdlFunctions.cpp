#include "SdlFunctions.h"
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
      TBFE_Base::MainConsole.write("   "+filename+" did not load correctly");
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
      TBFE_Base::MainConsole.write("texture fail");
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
    glOrtho(0,TBFE_Base::ScreenDimensions.X,TBFE_Base::ScreenDimensions.Y,0,1,10);
    glMatrixMode(GL_MODELVIEW);
    {
      glPushMatrix();
      glLoadIdentity();
      glTranslatef(x,y,-2);
      Position dimensions;
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
	  GLuint texture=TBFE_Base::GetTexture(source);
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
ModelData * loadModel(string model)
{
  Assimp::Importer importer;
  const aiScene * loadScene=importer.ReadFile(model.c_str(),aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);
  aiScene * scene=importer.GetOrphanedScene();
  ModelData * data=new ModelData();
  if (scene==NULL)
    {
      return NULL;
    };
  for (int i=0;i<scene->mNumMaterials;i++)
    {
      data->materials.push_back(scene->mMaterials[i]);
    };
  for (int i=0;i<scene->mNumMeshes;i++)
    {
      aiMesh * currentMesh=scene->mMeshes[i];
      MeshData * newMesh=new MeshData();
      for (int face=0;face<currentMesh->mNumFaces;face++)
	{
	  newMesh->indices.push_back(currentMesh->mFaces[face].mIndices[0]);
	  newMesh->indices.push_back(currentMesh->mFaces[face].mIndices[1]);
	  newMesh->indices.push_back(currentMesh->mFaces[face].mIndices[2]);
	};
      for (int i=0;i<currentMesh->mNumVertices;i++)
	{
	  newMesh->vertices.push_back(currentMesh->mVertices[i].x);
	  newMesh->vertices.push_back(currentMesh->mVertices[i].y);
	  newMesh->vertices.push_back(currentMesh->mVertices[i].z);
	  if (currentMesh->HasTextureCoords(0))
	    {
	      newMesh->texCoords.push_back(currentMesh->mTextureCoords[0][i]);
	    };
	  newMesh->normals.push_back(currentMesh->mNormals[i].x);
	  newMesh->normals.push_back(currentMesh->mNormals[i].y);
	  newMesh->normals.push_back(currentMesh->mNormals[i].z);
	};
      newMesh->material=currentMesh->mMaterialIndex;
      data->meshes.push_back(newMesh);
    };
  return data;
};
Uint32 getPixel( SDL_Surface *surface, int x, int y )
{
  if (surface==NULL)
    {
      TBFE_Base::MainConsole.write("surface does not exist");
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
void color4_to_float4(const struct aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void applyMaterial(const struct aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	struct aiColor4D diffuse;
	struct aiColor4D specular;
	struct aiColor4D ambient;
	struct aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	int max;
	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, (unsigned int *)&max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, (unsigned int *)&max);
	if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, (unsigned int *)&max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	glEnable(GL_CULL_FACE);
	if (mtl->GetTextureCount(aiTextureType_DIFFUSE))
	      {
		aiString newString;
		mtl->GetTexture(aiTextureType_DIFFUSE,0,&newString,NULL,NULL,NULL,NULL,NULL);
		glBindTexture(GL_TEXTURE_2D,TBFE_Base::GetTexture(TBFE_Base::CheckSheets(newString.data)));      
		glEnable(GL_TEXTURE_2D);
  	      }
	    else
	      {
		glDisable(GL_TEXTURE_2D);
	      };
};
void drawNodes(ModelData * model, aiVector3D position,aiVector3D rotation,aiVector3D scale)
{ 
  glPushMatrix();
  //glTranslatef(position[0],position[1],-position[2]);
  glTranslatef(position[0],position[1],position[2]);
  Quaternion rotationQuat=getQuaternionXYZ(rotation.x,rotation.y,rotation.z);
  glMultMatrixf(rotationQuat.toMatrix().dataPointer());
  for (int i=0;i<model->meshes.size();i++)
    {
      glPushMatrix();
      MeshData * currentMesh=model->meshes.at(i);
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glVertexPointer(3,GL_FLOAT,0,&currentMesh->vertices[0]);
      glNormalPointer(GL_FLOAT,0,&currentMesh->normals[0]);
      glTexCoordPointer(3,GL_FLOAT,sizeof(aiVector3D),&currentMesh->texCoords[0]);
      glDisable(GL_TEXTURE_2D);
      applyMaterial(model->materials[currentMesh->material]);
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
};

float roundDown(float num,int place)
{
  float newNum=floor(num*pow(10,place));
  newNum/=pow(10,place);
  return newNum;
};
PositionF applyRotations(PositionF position,Quaternion rotation)
{
  Matrix rotMatrix(rotation.X,rotation.Y,rotation.Z);
  Matrix idMatrix(1,0,0,0,
		  0,1,0,0,
		  0,0,1,0,
		  0,0,0,1);
  PositionF newPosition;
  rotMatrix=rotMatrix*idMatrix;
  newPosition.X=(rotMatrix[0]*position.X+rotMatrix[1]*position.Y+rotMatrix[2]*position.Z);

  newPosition.Y=(rotMatrix[4]*position.X+rotMatrix[5]*position.Y+rotMatrix[6]*position.Z);

  newPosition.Z=(rotMatrix[8]*position.X+rotMatrix[9]*position.Y+rotMatrix[10]*position.Z);
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
