%include <std_string.i>
%module PyActor
%import "tbfe/misc/PyMisc.i"
%{
#include "tbfe/actor/ActorCreate.h"
#include "tbfe/actor/Actor.h"
#include "tbfe/actor/Npc.h"
#include "tbfe/actor/NonLiving.h"
#include "tbfe/actor/Action.h"
#include "tbfe/actor/Animation.h"
#include "tbfe/actor/CollisionBox.h"
#include "tbfe/actor/Pulse.h"
%}
%include "tbfe/actor/ActorCreate.h"
%include "tbfe/actor/Actor.h"
%include "tbfe/actor/Npc.h"
%include "tbfe/actor/NonLiving.h"
%include "tbfe/actor/Action.h"
%include "tbfe/actor/Animation.h"
%include "tbfe/actor/CollisionBox.h"
%include "tbfe/actor/Pulse.h"
