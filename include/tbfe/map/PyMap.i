%include <std_string.i>
%module PyMap
%import "tbfe/misc/PyMisc.i"
%{
#include "tbfe/map/Map.h"
#include "tbfe/map/OverMap.h"
#include "tbfe/map/TileLayer.h"
%}
%include "tbfe/map/Map.h"
%include "tbfe/map/OverMap.h"
%include "tbfe/map/TileLayer.h"
