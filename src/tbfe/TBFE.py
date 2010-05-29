# This file was automatically generated by SWIG (http://www.swig.org).
# Version 1.3.40
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.
# This file is compatible with both classic and new-style classes.

from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_TBFE', [dirname(__file__)])
        except ImportError:
            import _TBFE
            return _TBFE
        if fp is not None:
            try:
                _mod = imp.load_module('_TBFE', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _TBFE = swig_import_helper()
    del swig_import_helper
else:
    import _TBFE
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
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
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


import Actor
import Misc
import Map
class TBFE(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBFE, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBFE, name)
    __repr__ = _swig_repr
    def createFile(self, *args): return _TBFE.TBFE_createFile(self, *args)
    def __init__(self): 
        this = _TBFE.new_TBFE()
        try: self.this.append(this)
        except: self.this = this
    def changeMap(self, *args): return _TBFE.TBFE_changeMap(self, *args)
    def initMap(self): return _TBFE.TBFE_initMap(self)
    def runEngine(self): return _TBFE.TBFE_runEngine(self)
    def addActor(self, *args): return _TBFE.TBFE_addActor(self, *args)
    def removeActor(self, *args): return _TBFE.TBFE_removeActor(self, *args)
    def addWindow(self, *args): return _TBFE.TBFE_addWindow(self, *args)
    def addTileSet(self, *args): return _TBFE.TBFE_addTileSet(self, *args)
    def addEvent(self, *args): return _TBFE.TBFE_addEvent(self, *args)
    def getEvent(self, *args): return _TBFE.TBFE_getEvent(self, *args)
    def getMousePosition(self): return _TBFE.TBFE_getMousePosition(self)
    def getMouseCenter(self): return _TBFE.TBFE_getMouseCenter(self)
    def setMouseCenter(self, *args): return _TBFE.TBFE_setMouseCenter(self, *args)
    def setShowMouse(self, *args): return _TBFE.TBFE_setShowMouse(self, *args)
    def getShowMouse(self): return _TBFE.TBFE_getShowMouse(self)
    def getCameraPosition(self): return _TBFE.TBFE_getCameraPosition(self)
    def addGlobalEvent(self, *args): return _TBFE.TBFE_addGlobalEvent(self, *args)
    __swig_destroy__ = _TBFE.delete_TBFE
    __del__ = lambda self : None;
TBFE_swigregister = _TBFE.TBFE_swigregister
TBFE_swigregister(TBFE)

class TBFE_Render(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBFE_Render, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBFE_Render, name)
    __repr__ = _swig_repr
    def refreshMapLayer(self, *args): return _TBFE.TBFE_Render_refreshMapLayer(self, *args)
    def __init__(self): 
        this = _TBFE.new_TBFE_Render()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _TBFE.delete_TBFE_Render
    __del__ = lambda self : None;
    def initializeTileSets(self): return _TBFE.TBFE_Render_initializeTileSets(self)
    def addTileSet(self, *args): return _TBFE.TBFE_Render_addTileSet(self, *args)
    def init(self): return _TBFE.TBFE_Render_init(self)
    def initGl(self): return _TBFE.TBFE_Render_initGl(self)
    def setLightPosition(self, *args): return _TBFE.TBFE_Render_setLightPosition(self, *args)
    def finalRender(self, *args): return _TBFE.TBFE_Render_finalRender(self, *args)
TBFE_Render_swigregister = _TBFE.TBFE_Render_swigregister
TBFE_Render_swigregister(TBFE_Render)

class TBFE_Logic(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBFE_Logic, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBFE_Logic, name)
    __repr__ = _swig_repr
    def getEvent(self): return _TBFE.TBFE_Logic_getEvent(self)
    def pollEvent(self): return _TBFE.TBFE_Logic_pollEvent(self)
    def isEventNew(self): return _TBFE.TBFE_Logic_isEventNew(self)
    def checkKeyDown(self, *args): return _TBFE.TBFE_Logic_checkKeyDown(self, *args)
    def setKeyDown(self, *args): return _TBFE.TBFE_Logic_setKeyDown(self, *args)
    def playerMovement(self): return _TBFE.TBFE_Logic_playerMovement(self)
    def textInput(self, *args): return _TBFE.TBFE_Logic_textInput(self, *args)
    def __init__(self): 
        this = _TBFE.new_TBFE_Logic()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _TBFE.delete_TBFE_Logic
    __del__ = lambda self : None;
TBFE_Logic_swigregister = _TBFE.TBFE_Logic_swigregister
TBFE_Logic_swigregister(TBFE_Logic)

class Console(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Console, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Console, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _TBFE.new_Console()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _TBFE.delete_Console
    __del__ = lambda self : None;
    def write(self, *args): return _TBFE.Console_write(self, *args)
    def errorMessage(self, *args): return _TBFE.Console_errorMessage(self, *args)
    def evalExpression(self, *args): return _TBFE.Console_evalExpression(self, *args)
    def runLine(self, *args): return _TBFE.Console_runLine(self, *args)
    def execute(self, *args): return _TBFE.Console_execute(self, *args)
    def getLine(self, *args): return _TBFE.Console_getLine(self, *args)
    def getNumberOfLines(self): return _TBFE.Console_getNumberOfLines(self)
    __swig_getmethods__["setPyInterface"] = lambda x: _TBFE.Console_setPyInterface
    if _newclass:setPyInterface = staticmethod(_TBFE.Console_setPyInterface)
Console_swigregister = _TBFE.Console_swigregister
Console_swigregister(Console)

def Console_setPyInterface(*args):
  return _TBFE.Console_setPyInterface(*args)
Console_setPyInterface = _TBFE.Console_setPyInterface



