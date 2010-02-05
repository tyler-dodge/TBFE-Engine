import sys
sys.path.append("TbfePy/")
import Tbfe
import Misc
import UI
import Actor
Tbfe.cvar.ScreenDimensions.X=1440
Tbfe.cvar.ScreenDimensions.Y=900
test=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(100,100)
test.changeMap("test.fmm")
test.initMap()
UI.loadWindows("Data/Types/Window.cfg")
frameRate=UI.createWindow(0,0,"FrameRate");
Console=UI.createWindow(10,20,"Console");
test.addWindow(frameRate)
test.addWindow(Console)
action=5
i=0
while action!=Misc.QUIT:
    action=test.runEngine()
    i+=1
    frameRate.selectElement("lblRate").setProperty("text",('%f' % (i)))
    frameRate.selectElement("lblRate").reload()
    

