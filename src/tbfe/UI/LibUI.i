%include <std_string.i>
%module UI
%import "../misc/LibMisc.i"
%{
#include "Window.cpp"
#include "Element.cpp"
#include "Label.cpp"
#include "StatBar.cpp"
#include "ImageBox.cpp"
#include "WindowCreate.cpp"
%}
%include "Window.h"
%include "Element.h"
%include "Label.h"
%include "StatBar.h"
%include "ImageBox.h"
%include "WindowCreate.h"
