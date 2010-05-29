%include <std_string.i>
%module UI
%import "../misc/LibMisc.i"
%{
#include "Window.h"
#include "Element.h"
#include "Label.h"
#include "StatBar.h"
#include "ImageBox.h"
#include "WindowCreate.h"
#include "TextBox.h"
%}
%include "Window.h"
%include "Element.h"
%include "Label.h"
%include "StatBar.h"
%include "ImageBox.h"
%include "WindowCreate.h"
%include "TextBox.h"
