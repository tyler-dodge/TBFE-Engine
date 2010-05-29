from TbfePy import Tbfe, Misc, UI, Actor
print(Tbfe.cvar)
Tbfe.cvar.ScreenDimensions.X=1024
Tbfe.cvar.ScreenDimensions.Y=600
def getEngine():
    global engine
    return engine
def initEngine():
    global engine
    engine=Tbfe.TBFE()
    UI.loadWindows("Data/Types/Window.cfg")
    Actor.loadActors("Data/Types/Actor.cfg")

    Tbfe.GetMainPlayer().setPositionF(100,0,1000)
    engine.changeMap("test.fmm")
    Tbfe.cvar.CurrentMap.generateMap(25,25)
    engine.initMap()
    return engine
