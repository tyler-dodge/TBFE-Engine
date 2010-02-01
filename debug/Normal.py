import sys
sys.path.append("TbfePy/")
import Tbfe
test=Tbfe.TBFE()
Tbfe.GetMainPlayer().setPosition(100,100)
Tbfe.cvar.CurrentMap.generateMap(20,20)
for i in range(0,100):
    test.runEngine()

