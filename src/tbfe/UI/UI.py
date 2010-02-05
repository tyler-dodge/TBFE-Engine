# This file was automatically generated by SWIG (http://www.swig.org).
# Version 1.3.36
#
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _UI
import new
new_instancemethod = new.instancemethod
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


import Misc
class Window(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Window, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Window, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _UI.new_Window(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _UI.delete_Window
    __del__ = lambda self : None;
    def renderElements(*args): return _UI.Window_renderElements(*args)
    def addElement(*args): return _UI.Window_addElement(*args)
    def selectElement(*args): return _UI.Window_selectElement(*args)
    def getDimensions(*args): return _UI.Window_getDimensions(*args)
    def setDimensions(*args): return _UI.Window_setDimensions(*args)
    def getScreenPosition(*args): return _UI.Window_getScreenPosition(*args)
    def setScreenPosition(*args): return _UI.Window_setScreenPosition(*args)
    def getVisibility(*args): return _UI.Window_getVisibility(*args)
    def setVisibility(*args): return _UI.Window_setVisibility(*args)
    def getShowBackground(*args): return _UI.Window_getShowBackground(*args)
    def setShowBackground(*args): return _UI.Window_setShowBackground(*args)
Window_swigregister = _UI.Window_swigregister
Window_swigregister(Window)

class Element(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Element, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Element, name)
    def __init__(self, *args, **kwargs): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def getBackground(*args): return _UI.Element_getBackground(*args)
    def setBackground(*args): return _UI.Element_setBackground(*args)
    def getPosition(*args): return _UI.Element_getPosition(*args)
    def setPosition(*args): return _UI.Element_setPosition(*args)
    def getDimensions(*args): return _UI.Element_getDimensions(*args)
    def setDimensions(*args): return _UI.Element_setDimensions(*args)
    def getName(*args): return _UI.Element_getName(*args)
    def setName(*args): return _UI.Element_setName(*args)
    def getProperty(*args): return _UI.Element_getProperty(*args)
    def setProperty(*args): return _UI.Element_setProperty(*args)
    def getVisibility(*args): return _UI.Element_getVisibility(*args)
    def setVisibility(*args): return _UI.Element_setVisibility(*args)
    def renderElement(*args): return _UI.Element_renderElement(*args)
    def reload(*args): return _UI.Element_reload(*args)
    __swig_destroy__ = _UI.delete_Element
    __del__ = lambda self : None;
Element_swigregister = _UI.Element_swigregister
Element_swigregister(Element)

class Label(Element):
    __swig_setmethods__ = {}
    for _s in [Element]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, Label, name, value)
    __swig_getmethods__ = {}
    for _s in [Element]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, Label, name)
    __repr__ = _swig_repr
    def renderElement(*args): return _UI.Label_renderElement(*args)
    def __init__(self, *args): 
        this = _UI.new_Label(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _UI.delete_Label
    __del__ = lambda self : None;
    def reload(*args): return _UI.Label_reload(*args)
Label_swigregister = _UI.Label_swigregister
Label_swigregister(Label)

class StatBar(Element):
    __swig_setmethods__ = {}
    for _s in [Element]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, StatBar, name, value)
    __swig_getmethods__ = {}
    for _s in [Element]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, StatBar, name)
    __repr__ = _swig_repr
    def renderElement(*args): return _UI.StatBar_renderElement(*args)
    def reload(*args): return _UI.StatBar_reload(*args)
    def __init__(self, *args): 
        this = _UI.new_StatBar(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _UI.delete_StatBar
    __del__ = lambda self : None;
StatBar_swigregister = _UI.StatBar_swigregister
StatBar_swigregister(StatBar)

class ImageBox(Element):
    __swig_setmethods__ = {}
    for _s in [Element]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ImageBox, name, value)
    __swig_getmethods__ = {}
    for _s in [Element]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ImageBox, name)
    __repr__ = _swig_repr
    def renderElement(*args): return _UI.ImageBox_renderElement(*args)
    def __init__(self, *args): 
        this = _UI.new_ImageBox(*args)
        try: self.this.append(this)
        except: self.this = this
    def reload(*args): return _UI.ImageBox_reload(*args)
    __swig_destroy__ = _UI.delete_ImageBox
    __del__ = lambda self : None;
ImageBox_swigregister = _UI.ImageBox_swigregister
ImageBox_swigregister(ImageBox)

loadWindows = _UI.loadWindows
addWindowType = _UI.addWindowType
getWindowType = _UI.getWindowType
createWindow = _UI.createWindow
deleteWindowList = _UI.deleteWindowList
class TextBox(Element):
    __swig_setmethods__ = {}
    for _s in [Element]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, TextBox, name, value)
    __swig_getmethods__ = {}
    for _s in [Element]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, TextBox, name)
    __repr__ = _swig_repr
    def renderElement(*args): return _UI.TextBox_renderElement(*args)
    def __init__(self, *args): 
        this = _UI.new_TextBox(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _UI.delete_TextBox
    __del__ = lambda self : None;
    def reload(*args): return _UI.TextBox_reload(*args)
TextBox_swigregister = _UI.TextBox_swigregister
TextBox_swigregister(TextBox)
cvar = _UI.cvar



