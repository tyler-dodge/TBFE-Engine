from TbfePy import Misc
class Tool:
    def __init__(self,startTile,finalTile):
        self.startTile=startTile
        self.createPlant=False
        self.finalTile=finalTile
    def use(self, tile):
        doAction=False
        if type(self.startTile)==tuple:
            for x in self.startTile:
                if x.Type==tile.Type and x.TileSet==tile.TileSet:
                    doAction=True
        else:
            if self.startTile.Type==tile.Type and self.startTile.TileSet==tile.TileSet:
                doAction=True
        if doAction:
            return self.finalTile
        else:
            return None
