from TbfePy import Misc, Actor
class PlantTool:
    def __init__(self,startTile,plantName):
        self.startTile=startTile
        self.createPlant=True
        self.plantName=plantName
    def use(self,tile):    
        doAction=False
        if type(self.startTile)==tuple:
            for x in self.startTile:
                if x.Type==tile.Type and x.TileSet==tile.TileSet:
                    doAction=True
        else:
            if self.startTile.Type==tile.Type and self.startTile.TileSet==tile.TileSet:
                doAction=True
        if doAction:
            newPlant=Actor.createActor(0,0,self.plantName,self.plantName)
            return newPlant
        else:
            return None
