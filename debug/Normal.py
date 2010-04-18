from TbfePy import Tbfe, Misc, UI, Actor
import math
class Console:
    def __init__(self,targetConsole,engine):
        self.window=UI.createWindow(0,0,"Console")
        self.window.getElement("txtLine").setProperty("border","1")
        self.window.getElement("ScrollUp").setProperty("border","1")
        self.window.getElement("ScrollDown").setProperty("border","1")
        self.window.getElement("lblEnter").setProperty("border","1")
        self.window.getElement("txtLine").setProperty("width",('%i' % (Tbfe.cvar.ScreenDimensions.X-140)))
        self.targetConsole=targetConsole
        self.debug=False
        writeEventLine="""elementTarget.getElement("txtLine").setProperty("text","");Tbfe.SetKeyTarget(elementTarget.getElement("txtLine"))"""
        engine.addEvent("Write",self.window.getElement("txtLine"),self.window,writeEventLine,Misc.CLICK)
        windowScroll="""("%i" % (int(elementTarget.getElement("txtData").getProperty("scrollY"))"""
        windowScrollUp=("%s-5))" % windowScroll)
        windowScrollDown=("%s+5))" % windowScroll)
        scrollUp=("""elementTarget.getElement("txtData").setProperty("scrollY",%s)""" % (windowScrollUp))
        scrollDown=("""elementTarget.getElement("txtData").setProperty("scrollY",%s)""" % (windowScrollDown))
        enterLine="""Tbfe.cvar.MainConsole.write(elementTarget.getElement("txtLine").getProperty("text"))"""
        enterLine=("""%s;Tbfe.cvar.MainConsole.runLine(elementTarget.getElement("txtLine").getProperty("text"))""" % (enterLine))
        engine.addEvent("ScrollUp",self.window.getElement("ScrollUp"),self.window,scrollUp,Misc.MOUSEHOLD)
        engine.addEvent("ScrollDown",self.window.getElement("ScrollDown"),self.window,scrollDown,Misc.MOUSEHOLD)
        engine.addEvent("EnterLine",self.window.getElement("lblEnter"),self.window,enterLine,Misc.MOUSEHOLD)
    def getWindow(self):
        return self.window
    def refreshWindow(self):
        consoleText=""
        for x in range(0,self.targetConsole.getNumberOfLines()):
            consoleText=('%s\n%s' % (consoleText,self.targetConsole.getLine(x)) )
        if self.debug==True:
            print(consoleText)
        self.window.getElement("txtData").setProperty("text",consoleText)
        self.window.getElement("txtData").reload()
def mouseCamera(MouseMovement):
    if engine.getShowMouse()!=True:
        cursorPosition=uiCursor.getScreenPosition()
        Position=Tbfe.getCameraAngle()
        Position.X-=MouseMovement.Y
        Rotation=Tbfe.GetMainPlayer().getRotationF()
        Rotation.Y-=MouseMovement.X
        Tbfe.GetMainPlayer().setRotationF(Rotation.X,Rotation.Y,Rotation.Z)
        if cursorPosition.Y<Tbfe.cvar.ScreenDimensions.Y/2-25 or Position.X<0:
            Position.X=0
            cursorPosition.Y-=int(MouseMovement.Y)
            if cursorPosition.Y>Tbfe.cvar.ScreenDimensions.Y/2-25:
                cursorPosition.Y=Tbfe.cvar.ScreenDimensions.Y/2-25
        if cursorPosition.Y>Tbfe.cvar.ScreenDimensions.Y/2-25 or Position.X>55:
            Position.X=55
            cursorPosition.Y-=int(MouseMovement.Y)
            if cursorPosition.Y<Tbfe.cvar.ScreenDimensions.Y/2-25:
                cursorPosition.Y=Tbfe.cvar.ScreenDimensions.Y/2-25
        if cursorPosition.Y>500:
            cursorPosition.Y=500
        if cursorPosition.Y<200:
            cursorPosition.Y=200
        #uiCursor.setScreenPosition(cursorPosition.X,cursorPosition.Y)
        Tbfe.setCameraAngle(Position.X,Position.Y,Position.Z)
def switchMouseCamera():
    if engine.getShowMouse():
        engine.setShowMouse(False)
    else:
        engine.setShowMouse(True)
def updatePulse():
    print("PULSING")
    rotation=Tbfe.getCameraAngle()
    magnitudePos=100
    position=engine.getCameraPosition()+Misc.applyRotations(Misc.PositionF(11,-10,75),rotation)
    pulse.setPositionF(position.X,position.Y,position.Z)
    pulse.setRotationF(-rotation.X,rotation.Y+180,rotation.Z,False)
    print("rotation:"+rotation.dumpString())
    #print("start:"+pulse.getPositionF().dumpString()+':'+engine.getCameraPosition().dumpString())
    num=pulse.collisionPulse()
    if num!=-1:
        uiCursor.getElement("lblTarget").setProperty("text",Tbfe.GetActorByNum(num).getConversation(False))
    else:
        uiCursor.getElement("lblTarget").setProperty("text","")
    pulseActor.setPositionF(pulsePosition.X,pulsePosition.Y,pulsePosition.Z)
    pulseActor.setRotationF(-rotation.X,-rotation.Y+180,-rotation.Z)
def pointer():
    cameraAngle=Tbfe.getCameraAngle()
    cameraPosition=engine.getCameraPosition()
    if cameraAngle.X>0 and cameraAngle.X<90:
        distance=(cameraPosition.Y-Tbfe.getCameraOffset().Y*20)/math.tan(cameraAngle.X*Misc.DEG_RAD)
        cursorPos=Misc.PositionF()
        cursorPos.X=math.sin(cameraAngle.Y*Misc.DEG_RAD)*distance
        cursorPos.Z=-math.cos(cameraAngle.Y*Misc.DEG_RAD)*distance
        cursorPos.X+=cameraPosition.X
        cursorPos.Z+=cameraPosition.Z
        #cursorPos.X=math.floor(cursorPos.X/100)*100
        #cursorPos.Z=math.floor(cursorPos.Z/100)*100
        #randomNpc.setPositionF(cursorPos.X,0,
        #                       cursorPos.Z)
        #randomNpc.getCollisionBox(0).setEnabled(False)
        #textProp=('Cam Pos:%s, Cam A:%s, Cur Ptr:%s' % (engine.getCameraPosition().dumpString(), 
        #                                               cameraAngle.dumpString(),
        #                                              randomNpc.getPositionF().dumpString()))
        #textProp=('%s, x %f, z %f, d %f' % (textProp,cursorPos.X,cursorPos.Z,distance))
        #uiMousePosition.getElement("lblRate").setProperty("text",textProp)
        return cursorPos
def normalTest():
    test=Misc.Quad()
    test.at(0).X=0
    test.at(0).Y=0
    test.at(0).Z=0

    test.at(1).X=1
    test.at(1).Y=0
    test.at(1).Z=0

    test.at(2).X=1
    test.at(2).Y=0
    test.at(2).Z=1

    test.at(3).X=1
    test.at(3).Y=0
    test.at(3).Z=1
def useTile():
    cursorPos=pointer()
    if cursorPos==None:
        return
    playerPos=Tbfe.GetMainPlayer().getPositionF()
    distance=math.pow(cursorPos.X-playerPos.X,2)
    distance+=math.pow(cursorPos.Y-playerPos.Y,2)
    distance+=math.pow(cursorPos.Z-playerPos.Z,2)
    distance=math.sqrt(distance)
    rCursorPos=Misc.PositionF()
    rCursorPos.X=math.floor(cursorPos.X/100)
    rCursorPos.Y=math.floor(cursorPos.Y/100)
    rCursorPos.Z=math.floor(cursorPos.Z/100)
    randomNpc.setPositionF(rCursorPos.X*100,rCursorPos.Y*100,rCursorPos.Z*100)
    if distance<200:
        newTile=Misc.Tile()
        newTile.Type=0
        newTile.TileSet=0
        newTile.Passability=0
        newTile.isChange=True
        Tbfe.cvar.CurrentMap.changeTile(int(rCursorPos.X)+1,int(rCursorPos.Z)+1,newTile,0)
def rotationTest():
    #180 225 180
    #270 180 225
    #270 0 315
    num=Misc.applyRotations(Misc.PositionF(0,0,1),
                            Misc.PositionF(0,-270,0))
    print(num.dumpString())
rotationTest()
Tbfe.cvar.ScreenDimensions.X=1024
Tbfe.cvar.ScreenDimensions.Y=600
engine=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(100,0,1000)
engine.changeMap("test.fmm")
Tbfe.cvar.CurrentMap.generateMap(25,25)
engine.initMap()
UI.loadWindows("Data/Types/Window.cfg")
Actor.loadActors("Data/Types/Actor.cfg")
uiConsole=Console(Tbfe.cvar.MainConsole,engine)
#engine.addWindow(uiConsole.getWindow())
uiMousePosition=UI.createWindow(0,400,"FrameRate")
engine.addWindow(uiMousePosition)
uiFrameRate=UI.createWindow(0,500,"FrameRate")
uiCursor=UI.createWindow(Tbfe.cvar.ScreenDimensions.X/2-25,Tbfe.cvar.ScreenDimensions.Y/2-25,"Cursor")
uiCursor.setShowBackground(False)
engine.addWindow(uiCursor)
engine.addWindow(uiFrameRate)
engine.setShowMouse(True)
action=5
i=0
randomNpc=Actor.createActor(20,1020,"Bed","Bed")
housing=Actor.createActor(0,400,"House","House")
pulseActor=Actor.createActor(0,0,"3dCursor","3dCursor")
engine.addActor(pulseActor)
engine.addActor(housing)
engine.addActor(randomNpc)
engine.addGlobalEvent("MouseCamera",Misc.MOUSEMOVE,0,"mouseCamera(mouseMovement)")
engine.addGlobalEvent("SwitchMouseControl",Misc.KEYPRESS,306,"switchMouseCamera()")
engine.addGlobalEvent("Action",Misc.KEYPRESS,32,"useTile()")
engine.setShowMouse(False)
Tbfe.setCameraAngle(0,90,0)
pulse=Actor.Pulse(Misc.PositionF(0,0,10),3,Misc.PositionF(0,0,0),400)
Tbfe.cvar.showCollision=True
while action!=Misc.QUIT:
    uiConsole.refreshWindow()
    action=engine.runEngine()
    mousePosition=engine.getMousePosition()
    
    uiMousePosition.getElement("lblRate").reload()
    uiFrameRate.getElement("lblRate").setProperty("text",('%f' % (60/Tbfe.cvar.GameSpeed)))
    uiFrameRate.getElement("lblRate").reload()
    Tbfe.GetMainPlayer().setRotationF(0,Tbfe.GetMainPlayer().getRotationF().Y,0)
    Tbfe.setCameraAngle(Tbfe.getCameraAngle().X,-Tbfe.GetMainPlayer().getRotationF().Y+90,Tbfe.getCameraAngle().Z)
    i+=1
    #randomNpc.setPositionF(engine.getCameraPosition().X,engine.getCameraPosition().Y,engine.getCameraPosition().Z)
    #randomNpc.setRotationF(Tbfe.getCameraAngle().X,-Tbfe.getCameraAngle().Y,Tbfe.getCameraAngle().Z)
    normalTest()
    updatePulse()
