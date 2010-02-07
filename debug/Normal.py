import sys
sys.path.append("TbfePy/")
import Tbfe
import Misc
import UI
import Actor
Tbfe.cvar.ScreenDimensions.X=1680
Tbfe.cvar.ScreenDimensions.Y=1050
test=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(100,100)
test.changeMap("test.fmm")
test.initMap()
UI.loadWindows("Data/Types/Window.cfg")
Console=UI.createWindow(0,0,"Console");
test.addWindow(Console)
action=5
i=0
while action!=Misc.QUIT:
    action=test.runEngine()
    i+=1
    

