#include "../misc/Structs.h"
#include "../misc/StringConversion.h"
#include "../Base.h"
#include "Actor.h"
#include "Npc.h"
#include "NonLiving.h"
#include <vector>
#ifndef ActorCreate_L
#define ActorCreate_L
extern vector<ActorType> actorTypeList;
extern Actor * createActor(int,int, std::string, std::string,std::string ActorName="None",bool WriteSuccess=true);
extern void loadActors(std::string);
extern void addActorType(std::string,std::string,std::string,std::string);
extern int getActorType(std::string);
extern void deleteCreatedActorList();
extern Actor * getActor(int);
#endif
