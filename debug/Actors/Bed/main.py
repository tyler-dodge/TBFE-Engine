from TbfePy import Actor, Misc
def StartAction(target):
    bed=Actor.Animation("bed.dae","0,",0,0.01,1,True)
    stand=Actor.Action("Stand","")
    bed.setRotation(270,180,0)
    bed.setOffset(4,0,0)
    stand.addAnimation(bed)
    target.addAction(stand)
    target.addCollisionBox(Misc.PositionF(0.1,0,0),Misc.PositionF(4,5,11))
    return
