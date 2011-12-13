#include <boost/python.hpp>
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/StringConversion.h"
#include "tbfe/Base.h"
#include "tbfe/actor/Actor.h"
#include "tbfe/actor/Npc.h"
#include "tbfe/actor/NonLiving.h"
#include "tbfe/actor/Pulse.h"
#include <vector>
#ifndef ActorCreate_L
#define ActorCreate_L
extern vector<ActorType> actorTypeList;
extern Actor * createActor(int,int, std::string, std::string,std::string ActorName="None",bool WriteSuccess=true);
extern void loadActors(std::string);
extern void addActorType(std::string,std::string,std::string,std::string);
extern int getActorType(std::string);
extern void deleteCreatedActorList(bool deleteMainPlayer=true);
extern Actor * getActor(int);
#endif
