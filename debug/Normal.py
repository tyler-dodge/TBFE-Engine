import sys
sys.path.append("TbfePy/")
import Tbfe
import Misc
Tbfe.cvar.ScreenDimensions.X=1440
Tbfe.cvar.ScreenDimensions.Y=900
test=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(100,100)
test.changeMap("test.fmm")
test.initMap()
action=5
while action!=Misc.QUIT:
    action=test.runEngine()
    

