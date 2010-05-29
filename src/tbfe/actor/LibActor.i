%include <std_string.i>
%module Actor
%import "../misc/LibMisc.i"
%{
#include "ActorCreate.h"
#include "Actor.h"
#include "Npc.h"
#include "NonLiving.h"
#include "Action.h"
#include "Animation.h"
#include "CollisionBox.h"
#include "Pulse.h"
%}
%include "ActorCreate.h"
%include "Actor.h"
%include "Npc.h"
%include "NonLiving.h"
%include "Action.h"
%include "Animation.h"
%include "CollisionBox.h"
%include "Pulse.h"
