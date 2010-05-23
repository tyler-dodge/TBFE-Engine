from TbfePy import Tbfe, Misc, UI, Actor
import Init
import math
class Cursor:
    uiCursor=uiCursor=UI.createWindow(Tbfe.cvar.ScreenDimensions.X/2-25,
                                       Tbfe.cvar.ScreenDimensions.Y/2-25,"Cursor")
    pulse=Actor.Pulse(Misc.PositionF(0,0,10),3,Misc.PositionF(0,0,0),300)
    def __init__(self,):
        self.uiCursor.setShowBackground(False)
        Init.getEngine().addWindow(self.uiCursor)
    def updatePulse(self):
    #print("PULSING")
        rotation=Tbfe.getCameraAngle()
        rotation.X=-rotation.X*0
        rotation.Y=rotation.Y+180
        magnitudePos=100
        position=Init.engine.getCameraPosition()+Misc.applyRotations(Misc.PositionF(0,0,250),
                                                                     Misc.PositionF(0*rotation.X,rotation.Y,
                                                                                    rotation.Z))
        self.pulse.setPositionF(position.X,position.Y,position.Z)
        self.pulse.setRotationF(rotation.X,rotation.Y,rotation.Z,False)
    #print("rotation:"+rotation.dumpString())
    #print("start:"+self.pulse.getPositionF().dumpString()+':'+Init.engine.getCameraPosition().dumpString())
        num=self.pulse.collisionPulse()
        if num!=-1:
            self.uiCursor.getElement("lblTarget").setProperty("text",Tbfe.GetActorByNum(num).getConversation(False))
        else:
            self.uiCursor.getElement("lblTarget").setProperty("text","")
    #self.pulseActor.setPositionF(pulsePosition.X,pulsePosition.Y,pulsePosition.Z)
    #pulseActor.setRotationF(-rotation.X,-rotation.Y+180,-rotation.Z)
    def get3dPointer(self,):
        cameraAngle=Tbfe.getCameraAngle()
        cameraPosition=Init.engine.getCameraPosition()
        if cameraAngle.X>0 and cameraAngle.X<90:
            distance=(cameraPosition.Y)/math.tan(cameraAngle.X*Misc.DEG_RAD)
            cursorPos=Misc.PositionF()
            cursorPos.X=math.sin(cameraAngle.Y*Misc.DEG_RAD)*distance
            cursorPos.Z=-math.cos(cameraAngle.Y*Misc.DEG_RAD)*distance
            cursorPos.X+=cameraPosition.X
            cursorPos.Z+=cameraPosition.Z
            return cursorPos
