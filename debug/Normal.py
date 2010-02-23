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
        engine.addEvent("ScrollUp",self.window.getElement("ScrollUp"),self.window,scrollUp,Misc.CLICK)
        engine.addEvent("ScrollDown",self.window.getElement("ScrollDown"),self.window,scrollDown,Misc.CLICK)
        engine.addEvent("EnterLine",self.window.getElement("lblEnter"),self.window,enterLine,Misc.CLICK)
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
Tbfe.cvar.ScreenDimensions.X=1024
Tbfe.cvar.ScreenDimensions.Y=600
engine=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(0,0)
engine.changeMap("test.fmm")
Tbfe.cvar.CurrentMap.generateMap(25,25)
engine.initMap()
Tbfe.cvar.MainConsole.write("test\nbob")
UI.loadWindows("Data/Types/Window.cfg")
uiConsole=Console(Tbfe.cvar.MainConsole,engine)
engine.addWindow(uiConsole.getWindow())
uiMousePosition=UI.createWindow(0,800,"FrameRate")
engine.addWindow(uiMousePosition)
action=5
i=0
while action!=Misc.QUIT:
    uiConsole.refreshWindow()
    action=engine.runEngine()
    mousePosition=engine.getMousePosition()
    uiMousePosition.getElement("lblRate").setProperty("text",('%i,%i' % (mousePosition.X,mousePosition.Y)))
    uiMousePosition.getElement("lblRate").reload()
    i+=1
