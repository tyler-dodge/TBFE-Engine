%include <std_string.i>
%module PyMisc
%{
#include "tbfe/misc/SdlFunctions.h"
#include "tbfe/misc/StringConversion.h"
#include "tbfe/misc/Timer.h"
#include "tbfe/misc/Matrix.h"
#include "tbfe/misc/Enums.h"
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/Quaternion.h"
#include "tbfe/misc/PositionF.h"
  %}
%include "tbfe/misc/SdlFunctions.h"
%include "tbfe/misc/StringConversion.h"
%include "tbfe/misc/Timer.h"
%include "tbfe/misc/Enums.h"
%include "tbfe/misc/Structs.h"
%ignore Matrix::operator[](int);
%include "tbfe/misc/Matrix.h"
%include "tbfe/misc/Quaternion.h"
%include "tbfe/misc/Matrix.h"
%include "tbfe/misc/PositionF.h"


%extend Matrix {
  float __getitem__(int index) {
    return (*self)[index];
  }
 };
