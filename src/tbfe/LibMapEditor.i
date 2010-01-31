%module MapEditor
%import "LibTbfe.i"
%import "actor/LibActor.i"
%import "map/LibMap.i"
%import "UI/LibUI.i"
%import "misc/LibMisc.i"
%{
#include "MapEditor.cpp"
%}
%include "MapEditor.h"