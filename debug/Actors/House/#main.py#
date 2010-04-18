from TbfePy import Actor
from TbfePy import Misc
def StartAction(target):
    House=Actor.Animation("house.dae","0,",0,0.01,1,True)
    Walk=Actor.Action("Stand","")
    House.setRotation(-90,0,0)
    Walk.addAnimation(House)
    target.addAction(Walk)
    collPosition=Misc.PositionF()
    collPosition.X=0
    collPosition.Y=0
    collPosition.Z=-1
    collDimensions=Misc.PositionF()
    collDimensions.X=13.5
    collDimensions.Y=10
    collDimensions.Z=1
    target.addCollisionBox(collPosition,collDimensions)
    collPosition.X=18.5
    collPosition.Y=0
    collPosition.Z=-1
    target.addCollisionBox(collPosition,collDimensions)

    collPosition.X=0
    collPosition.Y=0
    collPosition.Z=-20
    collDimensions.X=32
    collDimensions.Y=10
    collDimensions.Z=1
    target.addCollisionBox(collPosition,collDimensions)

    collPosition.X=0
    collPosition.Y=0
    collPosition.Z=-20
    collDimensions.X=1
    collDimensions.Y=10
    collDimensions.Z=20
    target.addCollisionBox(collPosition,collDimensions)
    
    collPosition.X=31
    collPosition.Y=0
    collPosition.Z=-20
    collDimensions.X=1
    collDimensions.Y=10
    collDimensions.Z=20
    target.addCollisionBox(collPosition,collDimensions)
    return
