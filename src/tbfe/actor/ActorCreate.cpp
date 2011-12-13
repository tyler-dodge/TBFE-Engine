#include "tbfe/actor/ActorCreate.h"
vector<ActorType> actorTypeList;
vector<Actor *> CreatedActorList;
void loadActors(std::string FileName)
{ 
  std::stringstream ConsoleWrite;
  ifstream ActorData(FileName.c_str(),ifstream::binary);
  if (ActorData==NULL)
    {
      TBFE_Base::MainConsole.errorMessage(0,FileName);
      return;
    };
  
  bool EndLoop=false;
  int i=0;
  while (i<100)
    {
      i++;
      loadString(&ActorData,';');
      std::string ActorName=loadString(&ActorData,':');
      if (ActorName=="")
	{
	  return;
	}
      loadString(&ActorData,'"');
      std::string ActorImageSource=loadString(&ActorData,'"');
      if (ActorImageSource=="")
	{
	  TBFE_Base::MainConsole.errorMessage(1,FileName); 
	  return;
	};     
      loadString(&ActorData,'"');
      std::string ActorScriptSource=loadString(&ActorData,'"');
      if (ActorScriptSource=="")
	{
	  TBFE_Base::MainConsole.errorMessage(1,FileName); 
	  return;
	}
      loadString(&ActorData,'"');
      std::string ActorConversation=loadString(&ActorData,'"');
      if (ActorConversation=="")
	{
	  TBFE_Base::MainConsole.errorMessage(1,FileName); 
	  return;
	}
      addActorType(ActorName,ActorScriptSource,ActorImageSource,ActorConversation);
    };
};

int getActorType(std::string ActorName)
{
  for (int i=0;i<actorTypeList.size();i++)
    {
      if (actorTypeList.at(i).Name==ActorName)
	{
	  return i;
	};
    };
  return -1;
};

void addActorType(std::string Name, std::string ScriptSource, std::string ImageSource, std::string Conversation)
{
  ActorType NewType;
  NewType.Name=Name;
  NewType.Script="Actors/"+Name+"/"+ScriptSource;
  NewType.Source="Actors/"+Name+"/"+ImageSource;
  NewType.Collision="Actors/"+Name+"/Collision.png";
  NewType.Conversation=Conversation;
  actorTypeList.push_back(NewType);
};
Actor * createActor(int PositionX,int PositionY, std::string ConversationText, std::string ActorTypeName, std::string ActorName,bool writeSuccess)
{
  std::stringstream ConsoleWrite;
  Actor * TempActor;
  
  SDL_Color ColorKey;
  ColorKey.r=0;
  ColorKey.g=255;
  ColorKey.b=0;
  int ActorTypeNum;
  if (ActorTypeName=="Npc")
    {
      ActorTypeNum=-2;
    }
  else
    {
      ActorTypeNum=getActorType(ActorTypeName);
    };
  if (ActorTypeNum==-1)
   { 
      ConsoleWrite << "Type " << ActorTypeName << " does not exist.";
      TBFE_Base::MainConsole.write(ConsoleWrite.str());
      return 0;
    };
  if (ActorTypeNum==-2)
    {
      TempActor=new Npc(PositionX,PositionY,ConversationText);
    }
  else
    {
      TempActor=new NonLiving(PositionX,PositionY,actorTypeList[ActorTypeNum]);
    };
  if (writeSuccess)				
    {
      ConsoleWrite << ActorTypeName << " Created";
      TBFE_Base::MainConsole.write(ConsoleWrite.str());
    };
  TempActor->setName(ActorName);
  CreatedActorList.push_back(TempActor);
  stringstream ActorSelf;
  ActorSelf << "Actor.getActor(" << CreatedActorList.size()-1 <<")";
  TBFE_Base::MainConsole.runLine("import Actors."+ActorTypeName+".main");
  TBFE_Base::MainConsole.runLine("Actors."+ActorTypeName+".main.StartAction("+ActorSelf.str()+")");
  return TempActor;
};
void deleteCreatedActorList(bool deleteMainPlayer)
{
  for (int i=0;i<CreatedActorList.size();i++)
    {
      if (CreatedActorList.at(i)!=NULL &&
	  (deleteMainPlayer || CreatedActorList.at(i)!=TBFE_Base::GetMainPlayer()))
	{
	  if (deleteMainPlayer)
	    {
	      TBFE_Base::SetMainPlayer(NULL);
	    };
	  delete CreatedActorList.at(i);
	};
    };
  CreatedActorList.resize(0);
};
Actor * getActor(int ActorNumber)
{
  if (ActorNumber<CreatedActorList.size())
    {
      return CreatedActorList.at(ActorNumber);
    };
  return NULL;
};
