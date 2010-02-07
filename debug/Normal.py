import sys
sys.path.append("TbfePy/")
import Tbfe
import Misc
import UI
import Actor
Tbfe.cvar.ScreenDimensions.X=1440
Tbfe.cvar.ScreenDimensions.Y=900
engine=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(100,100)
engine.changeMap("test.fmm")
Tbfe.cvar.CurrentMap.generateMap(25,25)
engine.initMap()
print("test")
UI.loadWindows("Data/Types/Window.cfg")
Console=UI.createWindow(0,0,"Console")
engine.addWindow(Console)
action=5
i=0
while action!=Misc.QUIT:
    action=engine.runEngine()
    i+=1
