%include <std_string.i>
%module Actor
%import "../misc/LibMisc.i"
%{
#include "ActorCreate.cpp"
#include "Actor.cpp"
#include "Npc.cpp"
#include "NonLiving.cpp"
#include "Inventory.cpp"
#include "Building.cpp"
#include "Action.cpp"
#include "Animation.cpp"
#include "CollisionBox.cpp"
%}
%include "ActorCreate.h"
%include "Actor.h"
%include "Npc.h"
%include "NonLiving.h"
%include "Inventory.h"
%include "Building.h"
%include "Action.h"
%include "Animation.h"
%include "CollisionBox.h"
