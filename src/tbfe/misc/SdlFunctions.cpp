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
void applyImage(int x,int y,SDL_Surface* source,SDL_Surface* target, SDL_Rect* clip)
{
  SDL_Rect offset;
  offset.x=x;
  offset.y=y;
  if (clip!=NULL && source!=NULL)
    {
      if (clip->x+clip->w > source->w || clip->y+clip->h > source->h)
	{
	  return;
	};
    };
  if (source!=NULL)
    {
      SDL_BlitSurface(source, clip, target, &offset);
    };
};
aiScene * loadModel(string model)
{
  Assimp::Importer importer;
  importer.ReadFile(model.c_str(),aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate );
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

void drawNodes( aiScene * scene, aiNode * currentNode, aiVector3D position,int angle, aiVector3D rotation, aiVector3D scale)
{
  if (currentNode==NULL || scene==NULL)
    {
      return;
    };
  glPushMatrix();
  glTranslatef(position[0],position[1],position[2]);
  glRotatef(angle,rotation[0],rotation[1],rotation[2]);
  for (int i=0;i<currentNode->mNumMeshes;i++)
    {
      aiMesh * currentMesh=scene->mMeshes[currentNode->mMeshes[i]];
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glVertexPointer(3,GL_FLOAT,0,currentMesh->mVertices);
      glNormalPointer(GL_FLOAT,0,currentMesh->mNormals);
      vector<int> indices;
      glBegin(GL_TRIANGLES);
      applyMaterial(scene->mMaterials[currentMesh->mMaterialIndex]);
      for (int i=0;i<currentMesh->mNumFaces;i++)
	{
	  for (int indice=0;indice<3;indice++)
	    {
	      indices.push_back(currentMesh->mFaces[i].mIndices[indice]);
	    };
	};
      glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,&indices[0]);
      glEnd();
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
    };
  glPopMatrix();
  for (int i=0;i<currentNode->mNumChildren;i++)
    {
      drawNodes(scene,currentNode->mChildren[i],position,angle,rotation,scale);
    };
};

