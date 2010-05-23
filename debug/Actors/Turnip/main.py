from TbfePy import Actor, Misc
def StartAction(target):
    #House=Actor.Animation("bed.dae","0,",0,0.01,1,True)
    #Walk=Actor.Action("Stand","")
    #House.setRotation(0,0,0)
    #Walk.addAnimation(House)
    #target.addAction(Walk)
    target.addCollisionBox(Misc.PositionF(1,0,1),Misc.PositionF(3,5,3))
    return
