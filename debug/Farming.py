from TbfePy import Tbfe, Misc, UI, Actor
import Cursor
def useTile():
    cursorPos=pointer()
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
    randomNpc.setPositionF(cursorPos.X,cursorPos.Y,cursorPos.Z)
    if distance<200:
        newTile=Misc.Tile()
        newTile.Type=0
        newTile.TileSet=0
        newTile.Passability=0
        newTile.isChange=True
        Tbfe.cvar.CurrentMap.changeTile(int(rCursorPos.X)+1,int(rCursorPos.Z)+1,newTile,0)
