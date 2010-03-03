#include "Base.h"
/* Private TBFE_Base
   extern vector<AnimationSheet> AnimationSheets;
   extern Actor * MainPlayer;
   extern Element *KeyTarget;
   extern Actor * Talker;
   extern TTF_Font *font;*/
namespace TBFE_Base
{
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
  aiScene * CheckModels(string source)
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
    sheet.Texture=bindImage(sheet.Data);
    sheet.Source=source;
    AnimationSheets.push_back(sheet);
    return sheet.Data;
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
	    return AnimationSheets.at(0).Texture;
	  };
      };
    return bindImage(surface);
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
};
