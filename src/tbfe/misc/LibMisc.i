%include <std_string.i>
%module Misc
%{
#include "SdlFunctions.cpp"
#include "StringConversion.cpp"
#include "Timer.cpp"
#include "Matrix.cpp"
#include "Enums.h"
#include "Structs.h"
#include "Quaternion.cpp"
  %}
%include "SdlFunctions.h"
%include "StringConversion.h"
%include "Timer.h"
%include "Enums.h"
%include "Structs.h"
%include "Matrix.h"
%include "Quaternion.h"
