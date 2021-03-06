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
#include "tbfe/misc/Position.h"
#include "tbfe/misc/TFont.h"
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
%include "tbfe/misc/Position.h"
%include "tbfe/misc/TFont.h"
%template(PositionI) Position<int>;
%template(PositionF) Position<float>;

%extend Matrix {
  float __getitem__(int index) {
    return (*self)[index];
  }
 };
