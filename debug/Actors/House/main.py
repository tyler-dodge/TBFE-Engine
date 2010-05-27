from TbfePy import Actor
from TbfePy import Misc
def StartAction(target):
    House=Actor.Animation("house.dae","0,",0,0.01,1,True)
    Walk=Actor.Action("Stand","")
    House.setRotation(Misc.Quaternion(1,0,0,-90))
    Walk.addAnimation(House)
    target.addAction(Walk)
    #front side-Left
    collPosition=Misc.PositionF()
    collPosition.X=0
    collPosition.Y=0
    collPosition.Z=-0.5
    collDimensions=Misc.PositionF()
    collDimensions.X=14
    collDimensions.Y=10
    collDimensions.Z=1
    target.addCollisionBox(collPosition,collDimensions)
    #front side-Right
    collPosition.X=18.1
    collPosition.Y=0
    collPosition.Z=-0.5
    collDimensions.X=13.9
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
