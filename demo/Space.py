import PyTbfe;
import PyMap;
print("Start");
engine=PyTbfe.TBFE(1366,768)
PyTbfe.cvar.CurrentMap.generateMap(25,25)
engine.initMap()
for x in range(0,1000):
    print(x)
    engine.runEngine()
