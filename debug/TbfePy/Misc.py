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
            fp, pathname, description = imp.find_module('_Misc', [dirname(__file__)])
        except ImportError:
            import _Misc
            return _Misc
        if fp is not None:
            try:
                _mod = imp.load_module('_Misc', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _Misc = swig_import_helper()
    del swig_import_helper
else:
    import _Misc
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



def applyImage(*args):
  return _Misc.applyImage(*args)
applyImage = _Misc.applyImage

def getPixel(*args):
  return _Misc.getPixel(*args)
getPixel = _Misc.getPixel

def loadModel(*args):
  return _Misc.loadModel(*args)
loadModel = _Misc.loadModel

def drawNodes(*args):
  return _Misc.drawNodes(*args)
drawNodes = _Misc.drawNodes

def applyMaterial(*args):
  return _Misc.applyMaterial(*args)
applyMaterial = _Misc.applyMaterial

def bindImage(*args):
  return _Misc.bindImage(*args)
bindImage = _Misc.bindImage

def roundDown(*args):
  return _Misc.roundDown(*args)
roundDown = _Misc.roundDown

def applyRotations(*args):
  return _Misc.applyRotations(*args)
applyRotations = _Misc.applyRotations

def convertToAngle(*args):
  return _Misc.convertToAngle(*args)
convertToAngle = _Misc.convertToAngle

def normalize(*args):
  return _Misc.normalize(*args)
normalize = _Misc.normalize

def absVal(*args):
  return _Misc.absVal(*args)
absVal = _Misc.absVal

def addNormals(*args):
  return _Misc.addNormals(*args)
addNormals = _Misc.addNormals

def crossProduct(*args):
  return _Misc.crossProduct(*args)
crossProduct = _Misc.crossProduct

def nextSet(*args):
  return _Misc.nextSet(*args)
nextSet = _Misc.nextSet

def nextChar(*args):
  return _Misc.nextChar(*args)
nextChar = _Misc.nextChar

def replaceString(*args):
  return _Misc.replaceString(*args)
replaceString = _Misc.replaceString
class Timer(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Timer, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Timer, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _Misc.new_Timer()
        try: self.this.append(this)
        except: self.this = this
    def Start(self): return _Misc.Timer_Start(self)
    def GetTicks(self): return _Misc.Timer_GetTicks(self)
    __swig_destroy__ = _Misc.delete_Timer
    __del__ = lambda self : None;
Timer_swigregister = _Misc.Timer_swigregister
Timer_swigregister(Timer)

def loadImage(*args):
  return _Misc.loadImage(*args)
loadImage = _Misc.loadImage

def loadString(*args):
  return _Misc.loadString(*args)
loadString = _Misc.loadString

PI = _Misc.PI
DEG_RAD = _Misc.DEG_RAD
RAD_DEG = _Misc.RAD_DEG
NONE = _Misc.NONE
GRASS = _Misc.GRASS
DIRT = _Misc.DIRT
DIRT_TILLED = _Misc.DIRT_TILLED
DIRT_TILLED_WATERED = _Misc.DIRT_TILLED_WATERED
DOWN = _Misc.DOWN
UP = _Misc.UP
LEFT = _Misc.LEFT
RIGHT = _Misc.RIGHT
QUIT = _Misc.QUIT
NORMAL = _Misc.NORMAL
SECOND = _Misc.SECOND
STANDING = _Misc.STANDING
AIMLESS = _Misc.AIMLESS
TALKING = _Misc.TALKING
CLICK = _Misc.CLICK
MOUSEHOLD = _Misc.MOUSEHOLD
MOUSEMOVE = _Misc.MOUSEMOVE
KEYPRESS = _Misc.KEYPRESS
class AnimationSheet(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, AnimationSheet, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, AnimationSheet, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Data"] = _Misc.AnimationSheet_Data_set
    __swig_getmethods__["Data"] = _Misc.AnimationSheet_Data_get
    if _newclass:Data = _swig_property(_Misc.AnimationSheet_Data_get, _Misc.AnimationSheet_Data_set)
    __swig_setmethods__["Source"] = _Misc.AnimationSheet_Source_set
    __swig_getmethods__["Source"] = _Misc.AnimationSheet_Source_get
    if _newclass:Source = _swig_property(_Misc.AnimationSheet_Source_get, _Misc.AnimationSheet_Source_set)
    __swig_setmethods__["Texture"] = _Misc.AnimationSheet_Texture_set
    __swig_getmethods__["Texture"] = _Misc.AnimationSheet_Texture_get
    if _newclass:Texture = _swig_property(_Misc.AnimationSheet_Texture_get, _Misc.AnimationSheet_Texture_set)
    __swig_setmethods__["isLoaded"] = _Misc.AnimationSheet_isLoaded_set
    __swig_getmethods__["isLoaded"] = _Misc.AnimationSheet_isLoaded_get
    if _newclass:isLoaded = _swig_property(_Misc.AnimationSheet_isLoaded_get, _Misc.AnimationSheet_isLoaded_set)
    def __init__(self): 
        this = _Misc.new_AnimationSheet()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_AnimationSheet
    __del__ = lambda self : None;
AnimationSheet_swigregister = _Misc.AnimationSheet_swigregister
AnimationSheet_swigregister(AnimationSheet)

class MeshData(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, MeshData, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, MeshData, name)
    __repr__ = _swig_repr
    __swig_setmethods__["indices"] = _Misc.MeshData_indices_set
    __swig_getmethods__["indices"] = _Misc.MeshData_indices_get
    if _newclass:indices = _swig_property(_Misc.MeshData_indices_get, _Misc.MeshData_indices_set)
    __swig_setmethods__["vertices"] = _Misc.MeshData_vertices_set
    __swig_getmethods__["vertices"] = _Misc.MeshData_vertices_get
    if _newclass:vertices = _swig_property(_Misc.MeshData_vertices_get, _Misc.MeshData_vertices_set)
    __swig_setmethods__["texCoords"] = _Misc.MeshData_texCoords_set
    __swig_getmethods__["texCoords"] = _Misc.MeshData_texCoords_get
    if _newclass:texCoords = _swig_property(_Misc.MeshData_texCoords_get, _Misc.MeshData_texCoords_set)
    __swig_setmethods__["normals"] = _Misc.MeshData_normals_set
    __swig_getmethods__["normals"] = _Misc.MeshData_normals_get
    if _newclass:normals = _swig_property(_Misc.MeshData_normals_get, _Misc.MeshData_normals_set)
    __swig_setmethods__["material"] = _Misc.MeshData_material_set
    __swig_getmethods__["material"] = _Misc.MeshData_material_get
    if _newclass:material = _swig_property(_Misc.MeshData_material_get, _Misc.MeshData_material_set)
    def __init__(self): 
        this = _Misc.new_MeshData()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_MeshData
    __del__ = lambda self : None;
MeshData_swigregister = _Misc.MeshData_swigregister
MeshData_swigregister(MeshData)

class ModelData(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ModelData, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ModelData, name)
    __repr__ = _swig_repr
    __swig_setmethods__["materials"] = _Misc.ModelData_materials_set
    __swig_getmethods__["materials"] = _Misc.ModelData_materials_get
    if _newclass:materials = _swig_property(_Misc.ModelData_materials_get, _Misc.ModelData_materials_set)
    __swig_setmethods__["meshes"] = _Misc.ModelData_meshes_set
    __swig_getmethods__["meshes"] = _Misc.ModelData_meshes_get
    if _newclass:meshes = _swig_property(_Misc.ModelData_meshes_get, _Misc.ModelData_meshes_set)
    def __init__(self): 
        this = _Misc.new_ModelData()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_ModelData
    __del__ = lambda self : None;
ModelData_swigregister = _Misc.ModelData_swigregister
ModelData_swigregister(ModelData)

class Model(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Model, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Model, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Data"] = _Misc.Model_Data_set
    __swig_getmethods__["Data"] = _Misc.Model_Data_get
    if _newclass:Data = _swig_property(_Misc.Model_Data_get, _Misc.Model_Data_set)
    __swig_setmethods__["Source"] = _Misc.Model_Source_set
    __swig_getmethods__["Source"] = _Misc.Model_Source_get
    if _newclass:Source = _swig_property(_Misc.Model_Source_get, _Misc.Model_Source_set)
    __swig_setmethods__["isLoaded"] = _Misc.Model_isLoaded_set
    __swig_getmethods__["isLoaded"] = _Misc.Model_isLoaded_get
    if _newclass:isLoaded = _swig_property(_Misc.Model_isLoaded_get, _Misc.Model_isLoaded_set)
    def __init__(self): 
        this = _Misc.new_Model()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_Model
    __del__ = lambda self : None;
Model_swigregister = _Misc.Model_swigregister
Model_swigregister(Model)

class Tile(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Tile, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Tile, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Misc.new_Tile(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_setmethods__["Type"] = _Misc.Tile_Type_set
    __swig_getmethods__["Type"] = _Misc.Tile_Type_get
    if _newclass:Type = _swig_property(_Misc.Tile_Type_get, _Misc.Tile_Type_set)
    __swig_setmethods__["TileSet"] = _Misc.Tile_TileSet_set
    __swig_getmethods__["TileSet"] = _Misc.Tile_TileSet_get
    if _newclass:TileSet = _swig_property(_Misc.Tile_TileSet_get, _Misc.Tile_TileSet_set)
    __swig_setmethods__["Passability"] = _Misc.Tile_Passability_set
    __swig_getmethods__["Passability"] = _Misc.Tile_Passability_get
    if _newclass:Passability = _swig_property(_Misc.Tile_Passability_get, _Misc.Tile_Passability_set)
    __swig_setmethods__["isChanged"] = _Misc.Tile_isChanged_set
    __swig_getmethods__["isChanged"] = _Misc.Tile_isChanged_get
    if _newclass:isChanged = _swig_property(_Misc.Tile_isChanged_get, _Misc.Tile_isChanged_set)
    __swig_destroy__ = _Misc.delete_Tile
    __del__ = lambda self : None;
Tile_swigregister = _Misc.Tile_swigregister
Tile_swigregister(Tile)

class Position(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Position, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Position, name)
    __repr__ = _swig_repr
    __swig_setmethods__["X"] = _Misc.Position_X_set
    __swig_getmethods__["X"] = _Misc.Position_X_get
    if _newclass:X = _swig_property(_Misc.Position_X_get, _Misc.Position_X_set)
    __swig_setmethods__["Y"] = _Misc.Position_Y_set
    __swig_getmethods__["Y"] = _Misc.Position_Y_get
    if _newclass:Y = _swig_property(_Misc.Position_Y_get, _Misc.Position_Y_set)
    __swig_setmethods__["Z"] = _Misc.Position_Z_set
    __swig_getmethods__["Z"] = _Misc.Position_Z_get
    if _newclass:Z = _swig_property(_Misc.Position_Z_get, _Misc.Position_Z_set)
    def __init__(self): 
        this = _Misc.new_Position()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_Position
    __del__ = lambda self : None;
Position_swigregister = _Misc.Position_swigregister
Position_swigregister(Position)

class CollidedTile(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CollidedTile, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CollidedTile, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Passability"] = _Misc.CollidedTile_Passability_set
    __swig_getmethods__["Passability"] = _Misc.CollidedTile_Passability_get
    if _newclass:Passability = _swig_property(_Misc.CollidedTile_Passability_get, _Misc.CollidedTile_Passability_set)
    __swig_setmethods__["position"] = _Misc.CollidedTile_position_set
    __swig_getmethods__["position"] = _Misc.CollidedTile_position_get
    if _newclass:position = _swig_property(_Misc.CollidedTile_position_get, _Misc.CollidedTile_position_set)
    def __init__(self): 
        this = _Misc.new_CollidedTile()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_CollidedTile
    __del__ = lambda self : None;
CollidedTile_swigregister = _Misc.CollidedTile_swigregister
CollidedTile_swigregister(CollidedTile)

class Property(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Property, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Property, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Name"] = _Misc.Property_Name_set
    __swig_getmethods__["Name"] = _Misc.Property_Name_get
    if _newclass:Name = _swig_property(_Misc.Property_Name_get, _Misc.Property_Name_set)
    __swig_setmethods__["Value"] = _Misc.Property_Value_set
    __swig_getmethods__["Value"] = _Misc.Property_Value_get
    if _newclass:Value = _swig_property(_Misc.Property_Value_get, _Misc.Property_Value_set)
    def __init__(self): 
        this = _Misc.new_Property()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_Property
    __del__ = lambda self : None;
Property_swigregister = _Misc.Property_swigregister
Property_swigregister(Property)

class ActorType(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ActorType, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ActorType, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Name"] = _Misc.ActorType_Name_set
    __swig_getmethods__["Name"] = _Misc.ActorType_Name_get
    if _newclass:Name = _swig_property(_Misc.ActorType_Name_get, _Misc.ActorType_Name_set)
    __swig_setmethods__["Source"] = _Misc.ActorType_Source_set
    __swig_getmethods__["Source"] = _Misc.ActorType_Source_get
    if _newclass:Source = _swig_property(_Misc.ActorType_Source_get, _Misc.ActorType_Source_set)
    __swig_setmethods__["Script"] = _Misc.ActorType_Script_set
    __swig_getmethods__["Script"] = _Misc.ActorType_Script_get
    if _newclass:Script = _swig_property(_Misc.ActorType_Script_get, _Misc.ActorType_Script_set)
    __swig_setmethods__["Collision"] = _Misc.ActorType_Collision_set
    __swig_getmethods__["Collision"] = _Misc.ActorType_Collision_get
    if _newclass:Collision = _swig_property(_Misc.ActorType_Collision_get, _Misc.ActorType_Collision_set)
    __swig_setmethods__["Conversation"] = _Misc.ActorType_Conversation_set
    __swig_getmethods__["Conversation"] = _Misc.ActorType_Conversation_get
    if _newclass:Conversation = _swig_property(_Misc.ActorType_Conversation_get, _Misc.ActorType_Conversation_set)
    def __init__(self): 
        this = _Misc.new_ActorType()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_ActorType
    __del__ = lambda self : None;
ActorType_swigregister = _Misc.ActorType_swigregister
ActorType_swigregister(ActorType)

class ElementList(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ElementList, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ElementList, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Name"] = _Misc.ElementList_Name_set
    __swig_getmethods__["Name"] = _Misc.ElementList_Name_get
    if _newclass:Name = _swig_property(_Misc.ElementList_Name_get, _Misc.ElementList_Name_set)
    __swig_setmethods__["Type"] = _Misc.ElementList_Type_set
    __swig_getmethods__["Type"] = _Misc.ElementList_Type_get
    if _newclass:Type = _swig_property(_Misc.ElementList_Type_get, _Misc.ElementList_Type_set)
    __swig_setmethods__["ElementPosition"] = _Misc.ElementList_ElementPosition_set
    __swig_getmethods__["ElementPosition"] = _Misc.ElementList_ElementPosition_get
    if _newclass:ElementPosition = _swig_property(_Misc.ElementList_ElementPosition_get, _Misc.ElementList_ElementPosition_set)
    __swig_setmethods__["Special"] = _Misc.ElementList_Special_set
    __swig_getmethods__["Special"] = _Misc.ElementList_Special_get
    if _newclass:Special = _swig_property(_Misc.ElementList_Special_get, _Misc.ElementList_Special_set)
    def __init__(self): 
        this = _Misc.new_ElementList()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_ElementList
    __del__ = lambda self : None;
ElementList_swigregister = _Misc.ElementList_swigregister
ElementList_swigregister(ElementList)

class WindowType(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, WindowType, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, WindowType, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Name"] = _Misc.WindowType_Name_set
    __swig_getmethods__["Name"] = _Misc.WindowType_Name_get
    if _newclass:Name = _swig_property(_Misc.WindowType_Name_get, _Misc.WindowType_Name_set)
    __swig_setmethods__["Elements"] = _Misc.WindowType_Elements_set
    __swig_getmethods__["Elements"] = _Misc.WindowType_Elements_get
    if _newclass:Elements = _swig_property(_Misc.WindowType_Elements_get, _Misc.WindowType_Elements_set)
    __swig_setmethods__["Width"] = _Misc.WindowType_Width_set
    __swig_getmethods__["Width"] = _Misc.WindowType_Width_get
    if _newclass:Width = _swig_property(_Misc.WindowType_Width_get, _Misc.WindowType_Width_set)
    __swig_setmethods__["Height"] = _Misc.WindowType_Height_set
    __swig_getmethods__["Height"] = _Misc.WindowType_Height_get
    if _newclass:Height = _swig_property(_Misc.WindowType_Height_get, _Misc.WindowType_Height_set)
    def __init__(self): 
        this = _Misc.new_WindowType()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_WindowType
    __del__ = lambda self : None;
WindowType_swigregister = _Misc.WindowType_swigregister
WindowType_swigregister(WindowType)

class EventType(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, EventType, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, EventType, name)
    __repr__ = _swig_repr
    __swig_setmethods__["Parent"] = _Misc.EventType_Parent_set
    __swig_getmethods__["Parent"] = _Misc.EventType_Parent_get
    if _newclass:Parent = _swig_property(_Misc.EventType_Parent_get, _Misc.EventType_Parent_set)
    __swig_setmethods__["TargetName"] = _Misc.EventType_TargetName_set
    __swig_getmethods__["TargetName"] = _Misc.EventType_TargetName_get
    if _newclass:TargetName = _swig_property(_Misc.EventType_TargetName_get, _Misc.EventType_TargetName_set)
    __swig_setmethods__["TargetElement"] = _Misc.EventType_TargetElement_set
    __swig_getmethods__["TargetElement"] = _Misc.EventType_TargetElement_get
    if _newclass:TargetElement = _swig_property(_Misc.EventType_TargetElement_get, _Misc.EventType_TargetElement_set)
    __swig_setmethods__["TargetEvent"] = _Misc.EventType_TargetEvent_set
    __swig_getmethods__["TargetEvent"] = _Misc.EventType_TargetEvent_get
    if _newclass:TargetEvent = _swig_property(_Misc.EventType_TargetEvent_get, _Misc.EventType_TargetEvent_set)
    __swig_setmethods__["Enabled"] = _Misc.EventType_Enabled_set
    __swig_getmethods__["Enabled"] = _Misc.EventType_Enabled_get
    if _newclass:Enabled = _swig_property(_Misc.EventType_Enabled_get, _Misc.EventType_Enabled_set)
    __swig_setmethods__["Function"] = _Misc.EventType_Function_set
    __swig_getmethods__["Function"] = _Misc.EventType_Function_get
    if _newclass:Function = _swig_property(_Misc.EventType_Function_get, _Misc.EventType_Function_set)
    __swig_setmethods__["Key"] = _Misc.EventType_Key_set
    __swig_getmethods__["Key"] = _Misc.EventType_Key_get
    if _newclass:Key = _swig_property(_Misc.EventType_Key_get, _Misc.EventType_Key_set)
    __swig_setmethods__["keyDown"] = _Misc.EventType_keyDown_set
    __swig_getmethods__["keyDown"] = _Misc.EventType_keyDown_get
    if _newclass:keyDown = _swig_property(_Misc.EventType_keyDown_get, _Misc.EventType_keyDown_set)
    def __init__(self): 
        this = _Misc.new_EventType()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_EventType
    __del__ = lambda self : None;
EventType_swigregister = _Misc.EventType_swigregister
EventType_swigregister(EventType)

class TileSheet(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TileSheet, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TileSheet, name)
    __repr__ = _swig_repr
    __swig_setmethods__["texture"] = _Misc.TileSheet_texture_set
    __swig_getmethods__["texture"] = _Misc.TileSheet_texture_get
    if _newclass:texture = _swig_property(_Misc.TileSheet_texture_get, _Misc.TileSheet_texture_set)
    __swig_setmethods__["dimensions"] = _Misc.TileSheet_dimensions_set
    __swig_getmethods__["dimensions"] = _Misc.TileSheet_dimensions_get
    if _newclass:dimensions = _swig_property(_Misc.TileSheet_dimensions_get, _Misc.TileSheet_dimensions_set)
    def __init__(self): 
        this = _Misc.new_TileSheet()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_TileSheet
    __del__ = lambda self : None;
TileSheet_swigregister = _Misc.TileSheet_swigregister
TileSheet_swigregister(TileSheet)

class Quad(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Quad, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Quad, name)
    __repr__ = _swig_repr
    __swig_setmethods__["points"] = _Misc.Quad_points_set
    __swig_getmethods__["points"] = _Misc.Quad_points_get
    if _newclass:points = _swig_property(_Misc.Quad_points_get, _Misc.Quad_points_set)
    def at(self, *args): return _Misc.Quad_at(self, *args)
    def __init__(self): 
        this = _Misc.new_Quad()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Misc.delete_Quad
    __del__ = lambda self : None;
Quad_swigregister = _Misc.Quad_swigregister
Quad_swigregister(Quad)

class Matrix(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Matrix, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Matrix, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Misc.new_Matrix(*args)
        try: self.this.append(this)
        except: self.this = this
    def __imul__(self, *args): return _Misc.Matrix___imul__(self, *args)
    def __mul__(self, *args): return _Misc.Matrix___mul__(self, *args)
    def dataPointer(self): return _Misc.Matrix_dataPointer(self)
    def Normalize(self): return _Misc.Matrix_Normalize(self)
    def dumpString(self): return _Misc.Matrix_dumpString(self)
    __swig_destroy__ = _Misc.delete_Matrix
    __del__ = lambda self : None;
Matrix_swigregister = _Misc.Matrix_swigregister
Matrix_swigregister(Matrix)

class Quaternion(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Quaternion, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Quaternion, name)
    __repr__ = _swig_repr
    __swig_setmethods__["x"] = _Misc.Quaternion_x_set
    __swig_getmethods__["x"] = _Misc.Quaternion_x_get
    if _newclass:x = _swig_property(_Misc.Quaternion_x_get, _Misc.Quaternion_x_set)
    __swig_setmethods__["y"] = _Misc.Quaternion_y_set
    __swig_getmethods__["y"] = _Misc.Quaternion_y_get
    if _newclass:y = _swig_property(_Misc.Quaternion_y_get, _Misc.Quaternion_y_set)
    __swig_setmethods__["z"] = _Misc.Quaternion_z_set
    __swig_getmethods__["z"] = _Misc.Quaternion_z_get
    if _newclass:z = _swig_property(_Misc.Quaternion_z_get, _Misc.Quaternion_z_set)
    __swig_setmethods__["w"] = _Misc.Quaternion_w_set
    __swig_getmethods__["w"] = _Misc.Quaternion_w_get
    if _newclass:w = _swig_property(_Misc.Quaternion_w_get, _Misc.Quaternion_w_set)
    def __init__(self, *args): 
        this = _Misc.new_Quaternion(*args)
        try: self.this.append(this)
        except: self.this = this
    def toMatrix(self): return _Misc.Quaternion_toMatrix(self)
    def __mul__(self, *args): return _Misc.Quaternion___mul__(self, *args)
    def normalize(self): return _Misc.Quaternion_normalize(self)
    __swig_destroy__ = _Misc.delete_Quaternion
    __del__ = lambda self : None;
Quaternion_swigregister = _Misc.Quaternion_swigregister
Quaternion_swigregister(Quaternion)

class PositionF(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, PositionF, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, PositionF, name)
    __repr__ = _swig_repr
    __swig_setmethods__["X"] = _Misc.PositionF_X_set
    __swig_getmethods__["X"] = _Misc.PositionF_X_get
    if _newclass:X = _swig_property(_Misc.PositionF_X_get, _Misc.PositionF_X_set)
    __swig_setmethods__["Y"] = _Misc.PositionF_Y_set
    __swig_getmethods__["Y"] = _Misc.PositionF_Y_get
    if _newclass:Y = _swig_property(_Misc.PositionF_Y_get, _Misc.PositionF_Y_set)
    __swig_setmethods__["Z"] = _Misc.PositionF_Z_set
    __swig_getmethods__["Z"] = _Misc.PositionF_Z_get
    if _newclass:Z = _swig_property(_Misc.PositionF_Z_get, _Misc.PositionF_Z_set)
    def __init__(self, *args): 
        this = _Misc.new_PositionF(*args)
        try: self.this.append(this)
        except: self.this = this
    def __add__(self, *args): return _Misc.PositionF___add__(self, *args)
    def __sub__(self, *args): return _Misc.PositionF___sub__(self, *args)
    def __iadd__(self, *args): return _Misc.PositionF___iadd__(self, *args)
    def __isub__(self, *args): return _Misc.PositionF___isub__(self, *args)
    def __div__(self, *args): return _Misc.PositionF___div__(self, *args)
    def dumpString(self): return _Misc.PositionF_dumpString(self)
    def __mul__(self, *args): return _Misc.PositionF___mul__(self, *args)
    __swig_destroy__ = _Misc.delete_PositionF
    __del__ = lambda self : None;
PositionF_swigregister = _Misc.PositionF_swigregister
PositionF_swigregister(PositionF)



