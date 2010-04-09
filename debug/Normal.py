from TbfePy import Tbfe, Misc, UI, Actor
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
        Position=engine.getCameraAngle()
        Position.X-=MouseMovement.Y
        Rotation=Tbfe.GetMainPlayer().getRotationF()
        Rotation.Y-=MouseMovement.X
        Tbfe.GetMainPlayer().setRotationF(Rotation.X,Rotation.Y,Rotation.Z)
        if cursorPosition.Y<Tbfe.cvar.ScreenDimensions.Y/2 or Position.X<0:
            Position.X=0
            cursorPosition.Y-=int(MouseMovement.Y)
            if cursorPosition.Y>Tbfe.cvar.ScreenDimensions.Y/2:
                cursorPosition.Y=Tbfe.cvar.ScreenDimensions.Y/2
        if cursorPosition.Y>Tbfe.cvar.ScreenDimensions.Y/2 or Position.X>55:
            Position.X=55
            cursorPosition.Y-=int(MouseMovement.Y)
            if cursorPosition.Y<Tbfe.cvar.ScreenDimensions.Y/2:
                cursorPosition.Y=Tbfe.cvar.ScreenDimensions.Y/2
        if cursorPosition.Y>500:
            cursorPosition.Y=500
        if cursorPosition.Y<200:
            cursorPosition.Y=200
        uiCursor.setScreenPosition(cursorPosition.X,cursorPosition.Y)
        engine.setCameraAngle(Position.X,Position.Y,Position.Z)
def switchMouseCamera():
    if engine.getShowMouse():
        engine.setShowMouse(False)
    else:
        engine.setShowMouse(True)
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
engine.addWindow(uiConsole.getWindow())
uiMousePosition=UI.createWindow(0,400,"FrameRate")
engine.addWindow(uiMousePosition)
uiFrameRate=UI.createWindow(0,500,"FrameRate")
uiCursor=UI.createWindow(Tbfe.cvar.ScreenDimensions.X/2,Tbfe.cvar.ScreenDimensions.Y/2,"Cursor")
engine.addWindow(uiCursor)
engine.addWindow(uiFrameRate)
engine.setShowMouse(True)
action=5
i=0
randomNpc=Actor.createActor(500,200,"Npc","Npc")
Tbfe.GetMainPlayer().setRotationF(0,180,0)
housing=Actor.createActor(0,400,"House","House")
engine.addActor(housing)
#engine.addActor(randomNpc)
engine.addGlobalEvent("MouseCamera",Misc.MOUSEMOVE,0,"mouseCamera(mouseMovement)")
engine.addGlobalEvent("SwitchMouseControl",Misc.KEYPRESS,306,"switchMouseCamera()")
engine.setShowMouse(False)
engine.setCameraAngle(0,90,0)
pulse=Actor.Pulse(0,0,200,5,Misc.PositionF(0,0,0),400)
num=pulse.collisionPulse()
print(Tbfe.GetActorByNum(num).getConversation(False))
print(Tbfe.GetActorByNum(num).getPositionF().dumpString())
while action!=Misc.QUIT:
    uiConsole.refreshWindow()
    action=engine.runEngine()
    mousePosition=engine.getMousePosition()
    uiMousePosition.getElement("lblRate").setProperty("text",('%i,%i' % (mousePosition.X,mousePosition.Y)))
    uiMousePosition.getElement("lblRate").reload()
    uiFrameRate.getElement("lblRate").setProperty("text",('%f' % (60/Tbfe.cvar.GameSpeed)))
    uiFrameRate.getElement("lblRate").reload()
    Tbfe.GetMainPlayer().setRotationF(0,Tbfe.GetMainPlayer().getRotationF().Y,0)
    i+=1
