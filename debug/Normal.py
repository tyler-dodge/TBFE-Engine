import sys
sys.path.append("TbfePy/")
import Tbfe
import Misc
import UI
import Actor
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
        Rotation=Tbfe.GetMainPlayer().getRotationF()
        Rotation.Y-=MouseMovement.X
        Tbfe.GetMainPlayer().setRotationF(Rotation.X,Rotation.Y,Rotation.Z)
        Position=engine.getCameraAngle()
        Position.X-=MouseMovement.Y
        #if Position.X<0:
        #    Position.X=0
        #if Position.X>90:
        #    Position.X=90
        engine.setCameraAngle(Position.X,Position.Y,Position.Z)
def switchMouseCamera():
    if engine.getShowMouse():
        engine.setShowMouse(False)
    else:
        engine.setShowMouse(True)
def house(newHouse):
    Body=Actor.Animation("house.dae","0,",0,0.01,1,True)
    Walk=Actor.Action("Walk","")
    Body.setRotation(-90,0,0)
    Walk.addAnimation(Body)
    newHouse.addAction(Walk)
Tbfe.cvar.ScreenDimensions.X=1024
Tbfe.cvar.ScreenDimensions.Y=600
engine=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(100,0,400)
engine.changeMap("test.fmm")
Tbfe.cvar.CurrentMap.generateMap(25,25)
engine.initMap()
UI.loadWindows("Data/Types/Window.cfg")
uiConsole=Console(Tbfe.cvar.MainConsole,engine)
engine.addWindow(uiConsole.getWindow())
uiMousePosition=UI.createWindow(0,400,"FrameRate")
engine.addWindow(uiMousePosition)
uiFrameRate=UI.createWindow(0,500,"FrameRate")
engine.addWindow(uiFrameRate)
engine.setShowMouse(True)
action=5
i=0
randomNpc=Actor.createActor(500,200,"Npc","Npc")
Tbfe.GetMainPlayer().setRotationF(0,180,0)
housing=Actor.createActor(0,0,"Npc","Npc")
house(housing)
engine.addActor(housing)
#engine.addActor(randomNpc)
engine.addGlobalEvent("MouseCamera",Misc.MOUSEMOVE,0,"mouseCamera(mouseMovement)")
engine.addGlobalEvent("SwitchMouseControl",Misc.KEYPRESS,306,"switchMouseCamera()")
engine.setShowMouse(False)
engine.setCameraAngle(0,90,0)
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
