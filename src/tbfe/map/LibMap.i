%include <std_string.i>
%module Map
%import "../misc/LibMisc.i"
%{
#include "Map.cpp"
#include "OverMap.cpp"
#include "TileLayer.cpp"
%}
%include "Map.h"
%include "OverMap.h"
%include "TileLayer.h"