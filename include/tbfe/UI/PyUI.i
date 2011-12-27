%include <std_string.i>
%module PyUI
%import "tbfe/misc/PyMisc.i"
%{
#include "tbfe/UI/Window.h"
#include "tbfe/UI/Element.h"
#include "tbfe/UI/Label.h"
#include "tbfe/UI/StatBar.h"
#include "tbfe/UI/ImageBox.h"
#include "tbfe/UI/TextBox.h"
%}
%include "tbfe/UI/Window.h"
%include "tbfe/UI/Element.h"
%include "tbfe/UI/Label.h"
%include "tbfe/UI/StatBar.h"
%include "tbfe/UI/ImageBox.h"
%include "tbfe/UI/TextBox.h"
