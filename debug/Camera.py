from TbfePy import Tbfe, Misc, UI, Actor
import math
import Init
import Cursor
def initCamera():
    Tbfe.setCameraAngle(0,90,0)
def mouseCamera(MouseMovement,cursor):
    if Init.getEngine().getShowMouse()!=True:
        cursorPosition=cursor.getScreenPosition()
        Position=Tbfe.getCameraAngle()
        Position.X-=MouseMovement.Y
        Rotation=Tbfe.GetMainPlayer().getRotationF()
        Rotation.Y-=MouseMovement.X
        Tbfe.GetMainPlayer().setRotationF(Rotation.X,Rotation.Y,Rotation.Z)
        if cursorPosition.Y<Tbfe.cvar.ScreenDimensions.Y/2-25 or Position.X<0:
            Position.X=0
            cursorPosition.Y-=int(MouseMovement.Y)
            if cursorPosition.Y>Tbfe.cvar.ScreenDimensions.Y/2-25:
                cursorPosition.Y=Tbfe.cvar.ScreenDimensions.Y/2-25
        if cursorPosition.Y>Tbfe.cvar.ScreenDimensions.Y/2-25 or Position.X>55:
            Position.X=55
            cursorPosition.Y-=int(MouseMovement.Y)
            if cursorPosition.Y<Tbfe.cvar.ScreenDimensions.Y/2-25:
                cursorPosition.Y=Tbfe.cvar.ScreenDimensions.Y/2-25
        if cursorPosition.Y>500:
            cursorPosition.Y=500
        if cursorPosition.Y<200:
            cursorPosition.Y=200
        #cursor.setScreenPosition(cursorPosition.X,cursorPosition.Y)
            Tbfe.setCameraAngle(Position.X,Position.Y,Position.Z)
def switchMouseCamera():
    if Init.getEngine().getShowMouse():
        Init.getEngine().setShowMouse(False)
    else:
        Init.getEngine().setShowMouse(True)
