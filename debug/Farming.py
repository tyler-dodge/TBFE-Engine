from TbfePy import Tbfe, Misc, UI, Actor
import Cursor, math,Init
def getPlants():
    global plants
    return plants
def initPlants():
    global plants
    plants={}
def useTile(tool,cursor):
    cursorPos=cursor.get3dPointer()
    if cursorPos==None:
        return
    playerPos=Tbfe.GetMainPlayer().getPositionF()
    distance=math.pow(cursorPos.X-playerPos.X,2)
    distance+=math.pow(cursorPos.Y-playerPos.Y,2)
    distance+=math.pow(cursorPos.Z-playerPos.Z,2)
    distance=math.sqrt(distance)
    rCursorPos=Misc.PositionF()
    rCursorPos.X=math.floor(cursorPos.X/100)
    rCursorPos.Y=math.floor(cursorPos.Y/100)
    rCursorPos.Z=math.floor(cursorPos.Z/100)
    if distance<200:
        newTile=tool.use(Tbfe.cvar.CurrentMap.getTile(int(rCursorPos.X)+1,int(rCursorPos.Z)+1,0))
        if newTile==None:
            return
        if tool.createPlant==False:
            Tbfe.cvar.CurrentMap.changeTile(int(rCursorPos.X)+1,int(rCursorPos.Z)+1,newTile,0)
            return
        test=newTile.checkActorCollision(rCursorPos.X*100+1,rCursorPos.Y*100,rCursorPos.Z*100+1)
        if test!=-1:
            return
        if tool.createPlant==True:
            rCursorPos=rCursorPos*100
            newTile.setPositionF(rCursorPos.X,rCursorPos.Y,rCursorPos.Z)
            plantArray=getPlants()
            Init.getEngine().addActor(newTile)
            plantArray[newTile]=newTile
