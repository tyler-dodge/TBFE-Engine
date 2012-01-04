%include <std_string.i>
%module PyTbfe
%import "tbfe/misc/PyMisc.i"
%import "tbfe/map/PyMap.i"
%{
#include "tbfe/Main.h"
#include "tbfe/Render.h"
#include "tbfe/Logic.h"
#include "tbfe/Console.h"
%}
%include "tbfe/Main.h"
%include "tbfe/Render.h"
%include "tbfe/Logic.h"
%include "tbfe/Console.h"
