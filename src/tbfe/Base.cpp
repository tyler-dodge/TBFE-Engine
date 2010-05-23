#include "Base.h"
/* Private TBFE_Base
   extern vector<AnimationSheet> AnimationSheets;
   extern Actor * MainPlayer;
   extern Element *KeyTarget;
   extern Actor * Talker;
   extern TTF_Font *font;*/
namespace TBFE_Base
{
  bool showCollision=false;
  SDL_Surface * CollisionTile=NULL;
  Console MainConsole;
  vector<Actor *> ActorList;
  vector<Window *> WindowList;
  Position ScreenDimensions;
  int TileSize=100;
  int NumberOfActors;  
  bool KeyControl;
  Map CurrentMap;
  int Time;
  Actor * Talker;
  Actor * MainPlayer=NULL;
  TTF_Font * font;
  Element * KeyTarget;
  float GameSpeed=1;
  vector<Model> ModelList;
  vector<AnimationSheet> AnimationSheets;
  vector<AnimationSheet> TempSheets;
  PositionF cameraAngle_(0,0,0);
  PositionF cameraOffset_(0,-6,0);
  PositionF cameraFollowOffset_(-1,-2.5,-4);
  int GetActorNum(Actor *actorPtr)
  {  
    for (int i=0;i<ActorList.size();i++)
      {
	if (ActorList.at(i)==actorPtr)
	  {
	    return i;
	  };
      };
    return -1;
  };
  Actor * GetActorByNum(int actorNum)
  {
    if (actorNum<ActorList.size())
      {
	return ActorList.at(actorNum);
      };
    return NULL;
  };
  TTF_Font * GetFont()
  {
    return font;
  };
  void SetFont(TTF_Font * newFont)
  {
    font=newFont;
  };
  SDL_Surface * GetCollisionTile()
  {
    return CollisionTile;
  };
  void SetCollisionTile(SDL_Surface * newTile)
  {
    CollisionTile=newTile;
  };
  ModelData * CheckModels(string source)
  {
    for (int i=0;i<ModelList.size();i++)
      {
	if (ModelList.at(i).Source==source)
	  {
	    return ModelList.at(i).Data;
	  };
      };
    Model newModel;
    newModel.Data=loadModel(source);
    if (newModel.Data==NULL)
      {
	return NULL;
      };
    newModel.Source=source;
    ModelList.push_back(newModel);
    return newModel.Data;
  };
  SDL_Surface * CheckSheets(string source)
  {
    for (int i=0;i<AnimationSheets.size();i++)
      {
	if (AnimationSheets.at(i).Source==source)
	  {
	    if (AnimationSheets.at(i).Texture==0)
	      {
		AnimationSheets.at(i).Texture=bindImage(AnimationSheets.at(i).Data);
	      };
	    return AnimationSheets.at(i).Data;
	  };
      };
    AnimationSheet sheet;
    sheet.Data=loadImage(source);
    if (sheet.Data==NULL)
      {
	return NULL;
      };
    AnimationSheets.push_back(sheet);
    int animNum=AnimationSheets.size()-1;
    AnimationSheets.at(animNum).Texture=bindImage(sheet.Data);
    AnimationSheets.at(animNum).Source=source;
    return AnimationSheets.at(animNum).Data;
  };
  string GetSheetName(SDL_Surface * newSheet)
  {
    for (int i=0;i<AnimationSheets.size();i++)
      {
	if (AnimationSheets.at(i).Data==newSheet)
	  {
	    return AnimationSheets.at(i).Source;
	  };
      };
    return "DNE";
  };
  GLuint GetTexture(SDL_Surface * surface)
  {
    for (int i=0;i<AnimationSheets.size();i++)
      {
	if (AnimationSheets.at(i).Data==surface)
	  {
	    if (AnimationSheets.at(i).Texture==0)
	      {
		AnimationSheets.at(i).Texture=bindImage(AnimationSheets.at(i).Data);
	      };
	    return AnimationSheets.at(i).Texture;
	  };
      };
    AnimationSheet tempSheet;
    tempSheet.Data=surface;
    tempSheet.Texture=bindImage(surface);
    
    TempSheets.push_back(tempSheet);
    return tempSheet.Texture;
  };
  void DeleteTempSheets()
  {
    //TempSheets do not delete SDL_Surfaces
    for (int i=0;i<TempSheets.size();i++)
      {
	if (TempSheets.at(i).Texture!=0)
	  {
	    glDeleteTextures(1,&TempSheets.at(i).Texture);
	  };
      };
    TempSheets.resize(0);
  };
  void DeleteAnimationSheets()
  {
    for (int i=0;i<AnimationSheets.size();i++)
      {
	if (AnimationSheets.at(i).Texture!=0)
	  {
	    glDeleteTextures(1,&AnimationSheets.at(i).Texture);
	  };
	//	if (AnimationSheets.at(i).Data!=NULL)
	//  {
	//    SDL_FreeSurface(AnimationSheets.at(i).Data);
	//  };
      };
    AnimationSheets.resize(0);
  };
  Actor * GetMainPlayer()
  {
    return MainPlayer;
  };
  void SetMainPlayer(Actor * newMainPlayer)
  {
    if (newMainPlayer!=NULL)
      {
	MainPlayer=newMainPlayer;
      };
  };
  Element * GetKeyTarget()
  {
    return KeyTarget;
  };
  void SetKeyTarget(Element * newTarget)
  {
    KeyTarget=newTarget;
  };
  
  Window * getWindowByNum(int windowNum)
  {
    if (WindowList.size()<windowNum || windowNum<0)
      {
	return NULL;
      };
    return WindowList.at(windowNum);
  };
  int getWindowNum(Window * targetWindow)
  {
    for (int i=0;i<WindowList.size();i++)
      {
	if (WindowList.at(i)==targetWindow)
	  {
	    return i;
	  };
      };
    return -1;
  };
  PositionF getCameraAngle()
  {
    return cameraAngle_;
  };
  void setCameraAngle(float x, float y, float z)
  {
    cameraAngle_.X=x;
    cameraAngle_.Y=y;
    cameraAngle_.Z=z;
  };
  PositionF getCameraFollowOffset()
  {
    return cameraFollowOffset_;
  };
  void setCameraFollowOffset(float x,float y,float z)
  {
    cameraFollowOffset_.X=x;
    cameraFollowOffset_.Y=y;
    cameraFollowOffset_.Z=z;
  };
  PositionF getCameraOffset()
  {
    return cameraOffset_;
  };
  void setCameraOffset(float x,float y,float z)
  {
    cameraOffset_.X=x;
    cameraOffset_.Y=y;
    cameraOffset_.Z=z;
  };
};
