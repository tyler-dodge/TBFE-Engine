from TbfePy import Actor, Misc
def StartAction(target):
    collPosition=Misc.PositionF()
    collPosition.X=-0.6
    collPosition.Y=0
    collPosition.Z=-2
    collDimensions=Misc.PositionF()
    collDimensions.X=1.2
    collDimensions.Y=7
    collDimensions.Z=2
    target.addCollisionBox(collPosition,collDimensions)
    return

