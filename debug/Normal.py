from TbfePy import Tbfe, Misc, UI, Actor
import Init
Init.initEngine()
engine=Init.getEngine()
import math
import Camera, Cursor, Console, Tool, Farming, PlantTool
print("BEGIN")
Farming.initPlants()
uiConsole=Console.Console(Tbfe.cvar.MainConsole)
uiFrameRate=UI.createWindow(0,500,"FrameRate")
uiStats=UI.createWindow(0,350,"Stats")
engine.addWindow(uiStats)
action=5
cursor3D=Actor.createActor(0,0,"Cursor3D","Cursor3D")
bed=Actor.createActor(520,160,"Bed","Bed")
housing=Actor.createActor(0,400,"House","House")
pulseActor=Actor.createActor(0,0,"PulseActor","PulseActor")
engine.addActor(pulseActor)
engine.addActor(housing)
engine.addActor(cursor3D)
engine.addActor(bed)
engine.addGlobalEvent("Action",Misc.KEYPRESS,32,"Farming.useTile(currentTool,mouseCursor)")
engine.addGlobalEvent("changeTool",Misc.KEYPRESS,122,"currentTool=seeds")
engine.addGlobalEvent("changeTool",Misc.KEYPRESS,120,"currentTool=hoe")
Tbfe.cvar.showCollision=True
Camera.initCamera()
engine.setShowMouse(False)
engine.addGlobalEvent("MouseCamera",Misc.MOUSEMOVE,0,"Camera.mouseCamera(mouseMovement,mouseCursor.uiCursor)")
engine.addGlobalEvent("SwitchMouseControl",Misc.KEYPRESS,306,"Camera.switchMouseCamera()")
mouseCursor=Cursor.Cursor()  
engine.addWindow(uiConsole.getWindow())
engine.addWindow(uiFrameRate)
hoe=Tool.Tool(Misc.Tile(2,0,0),Misc.Tile(3,0,0))
wateringCan=Tool.Tool(Misc.Tile(3,0,0),Misc.Tile(4,0,0))
seeds=PlantTool.PlantTool(Misc.Tile(3,0,0),"Turnip")
currentTool=hoe
i=0


while action!=Misc.QUIT:
    i=i+1

    Tbfe.setCameraAngle(0,i,0)
    action=engine.runEngine()    #uiConsole.refreshWindow()
    #Tbfe.GetMainPlayer().setRotationF(0,i,0)
    #Tbfe.setCameraAngle(45, -Tbfe.GetMainPlayer().getRotationF().Y+90,
    #                    Tbfe.getCameraAngle().Z)
    
    
    mouseCursor.updatePulse()
    pulseRotation=mouseCursor.pulse.getRotationF()
    #pulsePosition=mouseCursor.pulse.getPositionF()
    uiFrameRate.getElement("lblRate").setProperty("text",Tbfe.getCameraAngle().dumpString()+pulseRotation.dumpString())
    pulseActor.setPositionF(pulsePosition.X,pulsePosition.Y,pulsePosition.Z)
    pulseActor.setRotationF(pulseRotation.X,-pulseRotation.Y,pulseRotation.Z,False)
    #mousePosition=mouseCursor.get3dPointer()
    #if mousePosition!=None:
    #   mousePosition=mousePosition/100
    #  mousePosition.X=math.floor(mousePosition.X)
    # mousePosition.Y=math.floor(mousePosition.Y)
        #mousePosition.Z=math.floor(mousePosition.Z)
        #mousePosition=mousePosition*100
        #cursor3D.setPositionF(mousePosition.X,mousePosition.Y,mousePosition.Z)
