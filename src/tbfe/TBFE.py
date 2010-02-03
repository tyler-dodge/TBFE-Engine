# This file was automatically generated by SWIG (http://www.swig.org).
# Version 1.3.36
#
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _TBFE
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


import Actor
import Misc
import Map
DeleteAnimationSheets = _TBFE.DeleteAnimationSheets
GetActorNum = _TBFE.GetActorNum
GetActorByNum = _TBFE.GetActorByNum
CheckSheets = _TBFE.CheckSheets
GetFont = _TBFE.GetFont
SetFont = _TBFE.SetFont
GetCollisionTile = _TBFE.GetCollisionTile
SetCollisionTile = _TBFE.SetCollisionTile
GetMainPlayer = _TBFE.GetMainPlayer
SetMainPlayer = _TBFE.SetMainPlayer
class TBFE(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBFE, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBFE, name)
    __repr__ = _swig_repr
    def createFile(*args): return _TBFE.TBFE_createFile(*args)
    def __init__(self, *args): 
        this = _TBFE.new_TBFE(*args)
        try: self.this.append(this)
        except: self.this = this
    def changeMap(*args): return _TBFE.TBFE_changeMap(*args)
    def initMap(*args): return _TBFE.TBFE_initMap(*args)
    def runEngine(*args): return _TBFE.TBFE_runEngine(*args)
    def addActor(*args): return _TBFE.TBFE_addActor(*args)
    def removeActor(*args): return _TBFE.TBFE_removeActor(*args)
    def addWindow(*args): return _TBFE.TBFE_addWindow(*args)
    def addBuilding(*args): return _TBFE.TBFE_addBuilding(*args)
    def addTileSet(*args): return _TBFE.TBFE_addTileSet(*args)
    def addEvent(*args): return _TBFE.TBFE_addEvent(*args)
    def selectEvent(*args): return _TBFE.TBFE_selectEvent(*args)
    def addGlobalEvent(*args): return _TBFE.TBFE_addGlobalEvent(*args)
    __swig_destroy__ = _TBFE.delete_TBFE
    __del__ = lambda self : None;
TBFE_swigregister = _TBFE.TBFE_swigregister
TBFE_swigregister(TBFE)
cvar = _TBFE.cvar

class TBFE_Render(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBFE_Render, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBFE_Render, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _TBFE.new_TBFE_Render(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _TBFE.delete_TBFE_Render
    __del__ = lambda self : None;
    def initializeTileSets(*args): return _TBFE.TBFE_Render_initializeTileSets(*args)
    def addTileSet(*args): return _TBFE.TBFE_Render_addTileSet(*args)
    def changeLighting(*args): return _TBFE.TBFE_Render_changeLighting(*args)
    def init(*args): return _TBFE.TBFE_Render_init(*args)
    def finalRender(*args): return _TBFE.TBFE_Render_finalRender(*args)
TBFE_Render_swigregister = _TBFE.TBFE_Render_swigregister
TBFE_Render_swigregister(TBFE_Render)

class TBFE_Logic(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBFE_Logic, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBFE_Logic, name)
    __repr__ = _swig_repr
    def getEvent(*args): return _TBFE.TBFE_Logic_getEvent(*args)
    def pollEvent(*args): return _TBFE.TBFE_Logic_pollEvent(*args)
    def checkKeyDown(*args): return _TBFE.TBFE_Logic_checkKeyDown(*args)
    def setKeyDown(*args): return _TBFE.TBFE_Logic_setKeyDown(*args)
    def playerMovement(*args): return _TBFE.TBFE_Logic_playerMovement(*args)
    def contextAction(*args): return _TBFE.TBFE_Logic_contextAction(*args)
    def checkTalker(*args): return _TBFE.TBFE_Logic_checkTalker(*args)
    def textInput(*args): return _TBFE.TBFE_Logic_textInput(*args)
    def __init__(self, *args): 
        this = _TBFE.new_TBFE_Logic(*args)
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
    def __init__(self, *args): 
        this = _TBFE.new_Console(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _TBFE.delete_Console
    __del__ = lambda self : None;
    def write(*args): return _TBFE.Console_write(*args)
    def errorMessage(*args): return _TBFE.Console_errorMessage(*args)
    def runLine(*args): return _TBFE.Console_runLine(*args)
    def execute(*args): return _TBFE.Console_execute(*args)
    def getLine(*args): return _TBFE.Console_getLine(*args)
    def getNumberOfLines(*args): return _TBFE.Console_getNumberOfLines(*args)
Console_swigregister = _TBFE.Console_swigregister
Console_swigregister(Console)

class SunVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SunVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SunVector, name)
    __repr__ = _swig_repr
    __swig_setmethods__["CurrentPositionX"] = _TBFE.SunVector_CurrentPositionX_set
    __swig_getmethods__["CurrentPositionX"] = _TBFE.SunVector_CurrentPositionX_get
    if _newclass:CurrentPositionX = _swig_property(_TBFE.SunVector_CurrentPositionX_get, _TBFE.SunVector_CurrentPositionX_set)
    __swig_setmethods__["CurrentPositionY"] = _TBFE.SunVector_CurrentPositionY_set
    __swig_getmethods__["CurrentPositionY"] = _TBFE.SunVector_CurrentPositionY_get
    if _newclass:CurrentPositionY = _swig_property(_TBFE.SunVector_CurrentPositionY_get, _TBFE.SunVector_CurrentPositionY_set)
    __swig_setmethods__["Angle"] = _TBFE.SunVector_Angle_set
    __swig_getmethods__["Angle"] = _TBFE.SunVector_Angle_get
    if _newclass:Angle = _swig_property(_TBFE.SunVector_Angle_get, _TBFE.SunVector_Angle_set)
    __swig_setmethods__["Speed"] = _TBFE.SunVector_Speed_set
    __swig_getmethods__["Speed"] = _TBFE.SunVector_Speed_get
    if _newclass:Speed = _swig_property(_TBFE.SunVector_Speed_get, _TBFE.SunVector_Speed_set)
    def __init__(self, *args): 
        this = _TBFE.new_SunVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def Calculate(*args): return _TBFE.SunVector_Calculate(*args)
    __swig_destroy__ = _TBFE.delete_SunVector
    __del__ = lambda self : None;
SunVector_swigregister = _TBFE.SunVector_swigregister
SunVector_swigregister(SunVector)



