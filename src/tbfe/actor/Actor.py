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
            fp, pathname, description = imp.find_module('_Actor', [dirname(__file__)])
        except ImportError:
            import _Actor
            return _Actor
        if fp is not None:
            try:
                _mod = imp.load_module('_Actor', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _Actor = swig_import_helper()
    del swig_import_helper
else:
    import _Actor
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


import Misc

def loadActors(*args):
  return _Actor.loadActors(*args)
loadActors = _Actor.loadActors

def addActorType(*args):
  return _Actor.addActorType(*args)
addActorType = _Actor.addActorType

def getActorType(*args):
  return _Actor.getActorType(*args)
getActorType = _Actor.getActorType

def getActor(*args):
  return _Actor.getActor(*args)
getActor = _Actor.getActor
class Actor(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Actor, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Actor, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_Actor(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Actor.delete_Actor
    __del__ = lambda self : None;
    def startAction(self, *args): return _Actor.Actor_startAction(self, *args)
    def endCurrentAction(self): return _Actor.Actor_endCurrentAction(self)
    def runAction(self): return _Actor.Actor_runAction(self)
    def addAction(self, *args): return _Actor.Actor_addAction(self, *args)
    def getCurrentAction(self): return _Actor.Actor_getCurrentAction(self)
    def addCollisionBox(self, *args): return _Actor.Actor_addCollisionBox(self, *args)
    def getCollisionBox(self, *args): return _Actor.Actor_getCollisionBox(self, *args)
    def getNumCollisionBox(self): return _Actor.Actor_getNumCollisionBox(self)
    def getProperty(self, *args): return _Actor.Actor_getProperty(self, *args)
    def setProperty(self, *args): return _Actor.Actor_setProperty(self, *args)
    def changePosition(self, *args): return _Actor.Actor_changePosition(self, *args)
    def checkActorCollision(self, *args): return _Actor.Actor_checkActorCollision(self, *args)
    def getPositionF(self): return _Actor.Actor_getPositionF(self)
    def setPositionF(self, *args): return _Actor.Actor_setPositionF(self, *args)
    def getRotation(self): return _Actor.Actor_getRotation(self)
    def setRotation(self, *args): return _Actor.Actor_setRotation(self, *args)
    def rotate(self, *args): return _Actor.Actor_rotate(self, *args)
    def getSpeed(self): return _Actor.Actor_getSpeed(self)
    def setSpeed(self, *args): return _Actor.Actor_setSpeed(self, *args)
    def getScriptSource(self): return _Actor.Actor_getScriptSource(self)
    def setScriptSource(self, *args): return _Actor.Actor_setScriptSource(self, *args)
    def getName(self): return _Actor.Actor_getName(self)
    def setName(self, *args): return _Actor.Actor_setName(self, *args)
    def getBaseAction(self): return _Actor.Actor_getBaseAction(self)
    def setBaseAction(self, *args): return _Actor.Actor_setBaseAction(self, *args)
Actor_swigregister = _Actor.Actor_swigregister
Actor_swigregister(Actor)
cvar = _Actor.cvar

def createActor(*args):
  return _Actor.createActor(*args)
createActor = _Actor.createActor

def deleteCreatedActorList(deleteMainPlayer = True):
  return _Actor.deleteCreatedActorList(deleteMainPlayer)
deleteCreatedActorList = _Actor.deleteCreatedActorList

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
NonLiving_swigregister = _Actor.NonLiving_swigregister
NonLiving_swigregister(NonLiving)

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
    def addAnimation(self, *args): return _Actor.Action_addAnimation(self, *args)
    def getName(self): return _Actor.Action_getName(self)
    def setName(self, *args): return _Actor.Action_setName(self, *args)
    def getScript(self): return _Actor.Action_getScript(self)
    def setScript(self, *args): return _Actor.Action_setScript(self, *args)
    def getMainAnimationNum(self): return _Actor.Action_getMainAnimationNum(self)
    def setMainAnimation(self, *args): return _Actor.Action_setMainAnimation(self, *args)
    def animationPlus(self): return _Actor.Action_animationPlus(self)
    def loadAnimation(self): return _Actor.Action_loadAnimation(self)
    def getLayer(self, *args): return _Actor.Action_getLayer(self, *args)
    def getLayerSize(self): return _Actor.Action_getLayerSize(self)
    def reset(self): return _Actor.Action_reset(self)
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
    def getFrame(self): return _Actor.Animation_getFrame(self)
    def currentFramePlus(self): return _Actor.Animation_currentFramePlus(self)
    def loadModel(self): return _Actor.Animation_loadModel(self)
    def setModelSource(self, *args): return _Actor.Animation_setModelSource(self, *args)
    def getModel(self): return _Actor.Animation_getModel(self)
    def reset(self): return _Actor.Animation_reset(self)
    def getCurrentFrame(self): return _Actor.Animation_getCurrentFrame(self)
    def setCurrentFrame(self, *args): return _Actor.Animation_setCurrentFrame(self, *args)
    def getLoop(self): return _Actor.Animation_getLoop(self)
    def setLoop(self, *args): return _Actor.Animation_setLoop(self, *args)
    def getFinalFrame(self): return _Actor.Animation_getFinalFrame(self)
    def setFinalFrame(self, *args): return _Actor.Animation_setFinalFrame(self, *args)
    def getOffset(self): return _Actor.Animation_getOffset(self)
    def setOffset(self, *args): return _Actor.Animation_setOffset(self, *args)
    def getRotation(self): return _Actor.Animation_getRotation(self)
    def rotate(self, *args): return _Actor.Animation_rotate(self, *args)
    def setRotation(self, *args): return _Actor.Animation_setRotation(self, *args)
    def getRate(self): return _Actor.Animation_getRate(self)
    def setRate(self, *args): return _Actor.Animation_setRate(self, *args)
    __swig_destroy__ = _Actor.delete_Animation
    __del__ = lambda self : None;
Animation_swigregister = _Actor.Animation_swigregister
Animation_swigregister(Animation)

class CollisionBox(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CollisionBox, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CollisionBox, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_CollisionBox(*args)
        try: self.this.append(this)
        except: self.this = this
    def getDimensions(self): return _Actor.CollisionBox_getDimensions(self)
    def generatePoints(self, *args): return _Actor.CollisionBox_generatePoints(self, *args)
    def setDimensions(self, *args): return _Actor.CollisionBox_setDimensions(self, *args)
    def checkLine(self, *args): return _Actor.CollisionBox_checkLine(self, *args)
    def getPosition(self): return _Actor.CollisionBox_getPosition(self)
    def setPosition(self, *args): return _Actor.CollisionBox_setPosition(self, *args)
    def getCenter(self): return _Actor.CollisionBox_getCenter(self)
    def getRotation(self): return _Actor.CollisionBox_getRotation(self)
    def setRotation(self, *args): return _Actor.CollisionBox_setRotation(self, *args)
    def checkCollision(self, *args): return _Actor.CollisionBox_checkCollision(self, *args)
    def checkEnabled(self): return _Actor.CollisionBox_checkEnabled(self)
    def setEnabled(self, *args): return _Actor.CollisionBox_setEnabled(self, *args)
    __swig_destroy__ = _Actor.delete_CollisionBox
    __del__ = lambda self : None;
CollisionBox_swigregister = _Actor.CollisionBox_swigregister
CollisionBox_swigregister(CollisionBox)

class Pulse(Actor):
    __swig_setmethods__ = {}
    for _s in [Actor]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, Pulse, name, value)
    __swig_getmethods__ = {}
    for _s in [Actor]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, Pulse, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Actor.new_Pulse(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Actor.delete_Pulse
    __del__ = lambda self : None;
    def collisionPulse(self): return _Actor.Pulse_collisionPulse(self)
Pulse_swigregister = _Actor.Pulse_swigregister
Pulse_swigregister(Pulse)



