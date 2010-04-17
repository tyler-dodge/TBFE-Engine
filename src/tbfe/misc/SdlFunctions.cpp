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
	  //cout << start.X << "," << start.Y << ":" << end.X << "," << end.Y << "\n";
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
	      cout << "test\n";
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
void drawNodes(ModelData * model, aiVector3D position,aiVector3D rotation, aiVector3D scale)
{
  glPushMatrix();
  //glTranslatef(position[0],position[1],-position[2]);
  glTranslatef(position[0],position[1],position[2]);
  glRotatef(rotation[1],0,1,0);
  glRotatef(rotation[0],1,0,0);
  glRotatef(rotation[2],0,0,1);
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
PositionF applyRotations(PositionF position,PositionF rotation)
{
  float magnitude=sqrt(pow(position.Y,2)+pow(position.Z,2));
  PositionF tempPosition=position;
  //X rotation
  if (position.Y!=0)
    {
      position.Y=cos(convertToAngle(tempPosition.Y,tempPosition.Z)+rotation.X*PI/180)*magnitude;
      position.Z=sin(convertToAngle(tempPosition.Y,tempPosition.Z)+rotation.X*PI/180)*magnitude;
    }
  else
    {
      float angle;
      if (position.Z>0)
	{
	  angle=PI/2;
	}
      else
	{
	  angle=-PI/2;
	};
      position.Y=cos(angle+rotation.X*PI/180)*magnitude;
      position.Z=sin(angle+rotation.X*PI/180)*magnitude;
    };
  tempPosition=position;
  magnitude=sqrt(pow(position.X,2)+pow(position.Z,2));
  //Y rotation
  if (position.X!=0)
    {
      position.X=cos(convertToAngle(tempPosition.X,tempPosition.Z)+rotation.Y*PI/180)*magnitude;
      position.Z=sin(convertToAngle(tempPosition.X,tempPosition.Z)+rotation.Y*PI/180)*magnitude;
    }
  else
    {
      float angle;
      if (position.Z>0)
	{
	  angle=PI/2;
	}
      else
	{
	  angle=-PI/2;
	};
      position.X=cos(angle+rotation.Y*PI/180)*magnitude;
      position.Z=sin(angle+rotation.Y*PI/180)*magnitude;
    };
  tempPosition=position;
  magnitude=sqrt(pow(position.X,2)+pow(position.Y,2));
  //Z rotation
   if (position.X!=0)
    {
      position.X=cos(convertToAngle(tempPosition.X,tempPosition.Y)+rotation.Z*PI/180)*magnitude;
      position.Y=sin(convertToAngle(tempPosition.X,tempPosition.Y)+rotation.Z*PI/180)*magnitude;
   }
  else
    {
      float angle;
      if (position.Y>0)
	{
	  angle=PI/2;
	}
      else
	{
	  angle=-PI/2;
	};
      position.X=cos(angle+rotation.Z*PI/180)*magnitude;
      position.Y=sin(angle+rotation.Z*PI/180)*magnitude;
    };
  return position;
};
//Radians
float convertToAngle(float x,float y)
{
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
  PositionF finalNormal;
  float a=convertToAngle(normal.Z,normal.Y);
  finalNormal.Z=cos(a);
  finalNormal.Y=sin(a);
  float baseAngle=convertToAngle(normal.X,normal.Z);

  finalNormal=applyRotations(finalNormal,PositionF(0,baseAngle,0));
  return finalNormal;
};
PositionF normalize(Quad face, PositionF center)
{
  PositionF faceCenter=((face.points[0]+face.points[2])/2+(face.points[1]+face.points[3])/2)/2;
  PositionF xyNormal;
  PositionF zyNormal;
  PositionF normal;
  PositionF finalNormal;
  PositionF faceDiff=center-faceCenter;
  float a=convertToAngle(faceDiff.Z,
			 faceDiff.Y);
  zyNormal.Z=cos(a);
  zyNormal.Y=sin(a);

  a=convertToAngle(faceDiff.X,
		   faceDiff.Y);
  xyNormal.X=cos(a);
  xyNormal.Y=sin(a);
  return addNormals(xyNormal,zyNormal);
};
float absVal(float num)
{
  if (num<0)
    {
      num*=-1;
    };
  return num;
};
