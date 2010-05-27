def StartAction(target):
    House=Actor.Animation("bed.dae","0,",0,0.01,1,True)
    Walk=Actor.Action("Stand","")
    House.setRotation(Misc.Quaternion(1,0,0,-90))
    Walk.addAnimation(House)
    return
