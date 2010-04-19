from TbfePy import Tbfe, Misc, UI, Actor
import Init
Init.initEngine()
engine=Init.getEngine()
import math
import Camera
import Cursor
import Console
uiConsole=Console.Console(Tbfe.cvar.MainConsole)
uiFrameRate=UI.createWindow(0,500,"FrameRate")
print(uiConsole.getWindow().getScreenPosition())
action=5
cursor3D=Actor.createActor(0,0,"Cursor3D","Cursor3D")
bed=Actor.createActor(520,160,"Bed","Bed")
housing=Actor.createActor(0,400,"House","House")
pulseActor=Actor.createActor(0,0,"Cursor3D","Cursor3D")
#engine.addActor(pulseActor)
engine.addActor(housing)
engine.addActor(cursor3D)
engine.addActor(bed)
engine.addGlobalEvent("Action",Misc.KEYPRESS,32,"Farming.useTile()")
Tbfe.cvar.showCollision=True
Camera.initCamera()
engine.setShowMouse(False)
engine.addGlobalEvent("MouseCamera",Misc.MOUSEMOVE,0,"Camera.mouseCamera(mouseMovement,mouseCursor.uiCursor)")
engine.addGlobalEvent("SwitchMouseControl",Misc.KEYPRESS,306,"Camera.switchMouseCamera()")
mouseCursor=Cursor.Cursor()  
engine.addWindow(uiConsole.getWindow())
engine.addWindow(uiFrameRate)

while action!=Misc.QUIT:
    action=engine.runEngine()

    uiConsole.refreshWindow()
    uiFrameRate.getElement("lblRate").setProperty("text",('%f' % (60/Tbfe.cvar.GameSpeed)))
    uiFrameRate.getElement("lblRate").reload()
    Tbfe.GetMainPlayer().setRotationF(0,Tbfe.GetMainPlayer().getRotationF().Y,0)
    Tbfe.setCameraAngle(Tbfe.getCameraAngle().X,-Tbfe.GetMainPlayer().getRotationF().Y+90,
                        Tbfe.getCameraAngle().Z)
    
    mouseCursor.updatePulse()
    mousePosition=mouseCursor.get3dPointer()
    if mousePosition!=None:
        cursor3D.setPositionF(mousePosition.X,mousePosition.Y,mousePosition.Z)
