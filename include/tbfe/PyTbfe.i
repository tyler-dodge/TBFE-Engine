%include <std_string.i>
%module PyTbfe
%import "tbfe/actor/PyActor.i"
%import "tbfe/misc/PyMisc.i"
%import "tbfe/map/PyMap.i"
%{
#include "tbfe/Base.h"
#include "tbfe/Main.h"
#include "tbfe/Render.h"
#include "tbfe/Logic.h"
#include "tbfe/Console.h"
%}
%include "tbfe/Base.h"
%include "tbfe/Main.h"
%include "tbfe/Render.h"
%include "tbfe/Logic.h"
%include "tbfe/Console.h"
