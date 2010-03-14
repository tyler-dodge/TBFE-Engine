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
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glActiveTexture(texture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D,0,colors,textureSource->w,textureSource->h,0,format,
	       GL_UNSIGNED_BYTE,textureSource->pixels);
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
      glLoadIdentity();
      glPushMatrix();
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
	  glBindTexture(GL_TEXTURE_2D,texture);
	  glDisable(GL_DEPTH_TEST);
	  glDisable(GL_LIGHTING);
	  glBegin(GL_QUADS);
	  glTexCoord2f(start.X,start.Y);glVertex3f(0,0,0);
	  glTexCoord2f(start.X,start.Y+end.Y);glVertex3f(0,dimensions.Y,0);
	  glTexCoord2f(start.X+end.X,start.Y+end.Y);glVertex3f(dimensions.X,dimensions.Y,0);
	  glTexCoord2f(start.X+end.X,start.Y);glVertex3f(dimensions.X,0,0);
	  glEnd();
	  glDisable(GL_TEXTURE_2D);
	  glEnable(GL_LIGHTING);
	  glEnable(GL_DEPTH_TEST);
	};
      glPopMatrix();
    };
  };
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
};
aiScene * loadModel(string model)
{
  Assimp::Importer importer;
  const aiScene * test=importer.ReadFile(model.c_str(),aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);
  aiScene * newModel=importer.GetOrphanedScene();
  return newModel;
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
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, (unsigned int *)&max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else 
		glDisable(GL_CULL_FACE);
	
}
void drawNodes( aiScene * scene, aiNode * currentNode, aiVector3D position,aiVector3D rotation, aiVector3D scale)
{
  if (currentNode==NULL || scene==NULL)
    {
      return;
    };
  if (currentNode==scene->mRootNode)
    {
      glPushMatrix();
      //glTranslatef(position[0],position[1],-position[2]);
      glTranslatef(position[0],position[1],position[2]);
      glRotatef(rotation[1],0,1,0);
      glRotatef(rotation[0],1,0,0);
      glRotatef(rotation[2],0,0,1);
    };
  glPushMatrix();
  for (int i=0;i<currentNode->mNumMeshes;i++)
    {
      vector<GLuint> indices;
      indices.resize(0);
      aiMesh * currentMesh=scene->mMeshes[currentNode->mMeshes[i]];
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glVertexPointer(3,GL_FLOAT,0,currentMesh->mVertices);
      glNormalPointer(GL_FLOAT,0,currentMesh->mNormals);
      glTexCoordPointer(2,GL_FLOAT,0,currentMesh->mTextureCoords);
      applyMaterial(scene->mMaterials[currentMesh->mMaterialIndex]);
      for (int face=0;face<currentMesh->mNumFaces;face++)
	{
	  for (int indice=0;indice<3;indice++)
	    {
	      indices.push_back(currentMesh->mFaces[face].mIndices[indice]);
	    };
	};
      glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,&indices[0]);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
    };
  for (int i=0;i<currentNode->mNumChildren;i++)
    {
      drawNodes(scene,currentNode->mChildren[i],position,rotation,scale);
    };
  glPopMatrix();
  if (currentNode==scene->mRootNode)
    {
      glPopMatrix();
    };
};

float roundDown(float num,int place)
{
  float newNum=floor(num*pow(10,place));
  newNum/=pow(10,place);
  return newNum;
};
