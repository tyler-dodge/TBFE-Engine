%include <std_string.i>
%module Misc
%{
#include "SdlFunctions.cpp"
#include "StringConversion.cpp"
#include "Timer.cpp"
#include "Enums.h"
#include "Structs.h"
%}
%include "SdlFunctions.h"
%include "StringConversion.h"
%include "Timer.h"
%include "Enums.h"
%include "Structs.h"