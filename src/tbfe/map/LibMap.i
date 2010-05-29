%include <std_string.i>
%module Map
%import "../misc/LibMisc.i"
%{
#include "Map.h"
#include "OverMap.h"
#include "TileLayer.h"
%}
%include "Map.h"
%include "OverMap.h"
%include "TileLayer.h"
