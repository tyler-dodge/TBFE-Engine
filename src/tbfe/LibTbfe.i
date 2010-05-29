%include <std_string.i>
%module TBFE
%import "actor/LibActor.i"
%import "misc/LibMisc.i"
%import "map/LibMap.i"
%{
#include "Base.h"
#include "Main.h"
#include "Render.h"
#include "Logic.h"
#include "Console.h"
%}
%include "Base.h"
%include "Main.h"
%include "Render.h"
%include "Logic.h"
%include "Console.h"
