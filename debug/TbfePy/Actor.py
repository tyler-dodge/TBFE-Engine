# This file was automatically generated by SWIG (http://www.swig.org).
# Version 1.3.36
#
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _Actor
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
loadActors = _Actor.loadActors
addActorType = _Actor.addActorType
getActorType = _Actor.getActorType
deleteCreatedActorList = _Actor.deleteCreatedActorList
getActor = _Actor.getActor
class Actor(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Actor, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Actor, name)
    def __init__(self, *args, **kwargs): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _Actor.delete_Actor
    __del__ = lambda self : None;
    def startAction(*args): return _Actor.Actor_startAction(*args)
    def endCurrentAction(*args): return _Actor.Actor_endCurrentAction(*args)
    def runAction(*args): return _Actor.Actor_runAction(*args)
    def addAction(*args): return _Actor.Actor_addAction(*args)
    def getCurrentAction(*args): return _Actor.Actor_getCurrentAction(*args)
    def changePosition(*args): return _Actor.Actor_changePosition(*args)
    def changeScreen(*args): return _Actor.Actor_changeScreen(*args)
    def getCollisionRect(*args): return _Actor.Actor_getCollisionRect(*args)
    def getCollisionMap(*args): return _Actor.Actor_getCollisionMap(*args)
    def setCollisionMap(*args): return _Actor.Actor_setCollisionMap(*args)
    def loadCollisionMap(*args): return _Actor.Actor_loadCollisionMap(*args)
    def advancedCollision(*args): return _Actor.Actor_advancedCollision(*args)
    def checkActorCollision(*args): return _Actor.Actor_checkActorCollision(*args)
    def getPosition(*args): return _Actor.Actor_getPosition(*args)
    def setPosition(*args): return _Actor.Actor_setPosition(*args)
    def getPositionF(*args): return _Actor.Actor_getPositionF(*args)
    def setPositionF(*args): return _Actor.Actor_setPositionF(*args)
    def setDirection(*args): return _Actor.Actor_setDirection(*args)
    def getDirection(*args): return _Actor.Actor_getDirection(*args)
    def getConversation(*args): return _Actor.Actor_getConversation(*args)
    def setConversation(*args): return _Actor.Actor_setConversation(*args)
    def getSpeed(*args): return _Actor.Actor_getSpeed(*args)
    def setSpeed(*args): return _Actor.Actor_setSpeed(*args)
    def getScriptSource(*args): return _Actor.Actor_getScriptSource(*args)
    def setScriptSource(*args): return _Actor.Actor_setScriptSource(*args)
    def getName(*args): return _Actor.Actor_getName(*args)
    def setName(*args): return _Actor.Actor_setName(*args)
    def getBaseAction(*args): return _Actor.Actor_getBaseAction(*args)
    def setBaseAction(*args): return _Actor.Actor_setBaseAction(*args)
    def getCollisionDimensions(*args): return _Actor.Actor_getCollisionDimensions(*args)
    def setCollisionDimensions(*args): return _Actor.Actor_setCollisionDimensions(*args)
    def getWalking(*args): return _Actor.Actor_getWalking(*args)
    def setWalking(*args): return _Actor.Actor_setWalking(*args)
    def getMobile(*args): return _Actor.Actor_getMobile(*args)
    def setMobile(*args): return _Actor.Actor_setMobile(*args)
    def harvest(*args): return _Actor.Actor_harvest(*args)
    def getDirOffset(*args): return _Actor.Actor_getDirOffset(*args)
Actor_swigregister = _Actor.Actor_swigregister
Actor_swigregister(Actor)
cvar = _Actor.cvar
createActor = _Actor.createActor

class Npc(Actor):
    __swig_setmethods__ = {}
    for _s in [Actor]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, Npc, name, value)
    __swig_getmethods__ = {}
    for _s in [Actor]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, Npc, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_Npc(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Actor.delete_Npc
    __del__ = lambda self : None;
    def getConversation(*args): return _Actor.Npc_getConversation(*args)
Npc_swigregister = _Actor.Npc_swigregister
Npc_swigregister(Npc)

class NonLiving(Actor):
    __swig_setmethods__ = {}
    for _s in [Actor]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, NonLiving, name, value)
    __swig_getmethods__ = {}
    for _s in [Actor]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, NonLiving, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_NonLiving(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Actor.delete_NonLiving
    __del__ = lambda self : None;
    def getConversation(*args): return _Actor.NonLiving_getConversation(*args)
NonLiving_swigregister = _Actor.NonLiving_swigregister
NonLiving_swigregister(NonLiving)

class Inventory(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Inventory, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Inventory, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_Inventory(*args)
        try: self.this.append(this)
        except: self.this = this
    def get(*args): return _Actor.Inventory_get(*args)
    def getAmount(*args): return _Actor.Inventory_getAmount(*args)
    def remove(*args): return _Actor.Inventory_remove(*args)
    def set(*args): return _Actor.Inventory_set(*args)
    def add(*args): return _Actor.Inventory_add(*args)
    def getStackable(*args): return _Actor.Inventory_getStackable(*args)
    def setStackable(*args): return _Actor.Inventory_setStackable(*args)
    __swig_destroy__ = _Actor.delete_Inventory
    __del__ = lambda self : None;
Inventory_swigregister = _Actor.Inventory_swigregister
Inventory_swigregister(Inventory)

class Building(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Building, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Building, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_Building(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Actor.delete_Building
    __del__ = lambda self : None;
    def getFloorTile(*args): return _Actor.Building_getFloorTile(*args)
    def getRoofTile(*args): return _Actor.Building_getRoofTile(*args)
    def getPosition(*args): return _Actor.Building_getPosition(*args)
    def setPosition(*args): return _Actor.Building_setPosition(*args)
    def getFloorDimensions(*args): return _Actor.Building_getFloorDimensions(*args)
    def setFloorDimensions(*args): return _Actor.Building_setFloorDimensions(*args)
    def getRoofDimensions(*args): return _Actor.Building_getRoofDimensions(*args)
    def setRoofDimensions(*args): return _Actor.Building_setRoofDimensions(*args)
    def getWall(*args): return _Actor.Building_getWall(*args)
    def getNumberOfWalls(*args): return _Actor.Building_getNumberOfWalls(*args)
Building_swigregister = _Actor.Building_swigregister
Building_swigregister(Building)

class Action(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Action, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Action, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_Action(*args)
        try: self.this.append(this)
        except: self.this = this
    def addAnimation(*args): return _Actor.Action_addAnimation(*args)
    def getName(*args): return _Actor.Action_getName(*args)
    def setName(*args): return _Actor.Action_setName(*args)
    def getScript(*args): return _Actor.Action_getScript(*args)
    def setScript(*args): return _Actor.Action_setScript(*args)
    def getMainAnimationNum(*args): return _Actor.Action_getMainAnimationNum(*args)
    def setMainAnimation(*args): return _Actor.Action_setMainAnimation(*args)
    def setDirection(*args): return _Actor.Action_setDirection(*args)
    def getDirection(*args): return _Actor.Action_getDirection(*args)
    def getFrameRect(*args): return _Actor.Action_getFrameRect(*args)
    def animationPlus(*args): return _Actor.Action_animationPlus(*args)
    def loadAnimation(*args): return _Actor.Action_loadAnimation(*args)
    def getLayer(*args): return _Actor.Action_getLayer(*args)
    def getLayerSize(*args): return _Actor.Action_getLayerSize(*args)
    def reset(*args): return _Actor.Action_reset(*args)
    __swig_destroy__ = _Actor.delete_Action
    __del__ = lambda self : None;
Action_swigregister = _Actor.Action_swigregister
Action_swigregister(Action)

class Animation(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Animation, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Animation, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_Animation(*args)
        try: self.this.append(this)
        except: self.this = this
    def getFrame(*args): return _Actor.Animation_getFrame(*args)
    def getFrameRect(*args): return _Actor.Animation_getFrameRect(*args)
    def currentFramePlus(*args): return _Actor.Animation_currentFramePlus(*args)
    def loadSheet(*args): return _Actor.Animation_loadSheet(*args)
    def setSheetSource(*args): return _Actor.Animation_setSheetSource(*args)
    def getSheet(*args): return _Actor.Animation_getSheet(*args)
    def reset(*args): return _Actor.Animation_reset(*args)
    def getCurrentFrame(*args): return _Actor.Animation_getCurrentFrame(*args)
    def setCurrentFrame(*args): return _Actor.Animation_setCurrentFrame(*args)
    def getDimensions(*args): return _Actor.Animation_getDimensions(*args)
    def setDimensions(*args): return _Actor.Animation_setDimensions(*args)
    def getLoop(*args): return _Actor.Animation_getLoop(*args)
    def setLoop(*args): return _Actor.Animation_setLoop(*args)
    def getStartX(*args): return _Actor.Animation_getStartX(*args)
    def setStartX(*args): return _Actor.Animation_setStartX(*args)
    def getFinalFrame(*args): return _Actor.Animation_getFinalFrame(*args)
    def setFinalFrame(*args): return _Actor.Animation_setFinalFrame(*args)
    def getOffset(*args): return _Actor.Animation_getOffset(*args)
    def setOffset(*args): return _Actor.Animation_setOffset(*args)
    def getRate(*args): return _Actor.Animation_getRate(*args)
    def setRate(*args): return _Actor.Animation_setRate(*args)
    __swig_destroy__ = _Actor.delete_Animation
    __del__ = lambda self : None;
Animation_swigregister = _Actor.Animation_swigregister
Animation_swigregister(Animation)



