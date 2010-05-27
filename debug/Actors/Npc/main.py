from TbfePy import Actor, Misc
def StartAction(target):
    collPosition=Misc.PositionF()
    collPosition.X=-0.2
    collPosition.Y=0
    collPosition.Z=-0.6
    collDimensions=Misc.PositionF()
    collDimensions.X=2
    collDimensions.Y=8
    collDimensions.Z=1.2
    target.addCollisionBox(collPosition,collDimensions)
    return

