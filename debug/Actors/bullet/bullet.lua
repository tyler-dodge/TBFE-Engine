function StartAction()
   HoldPistol=Actor.Action("Walk","")
   bullet=Actor.Animation("Actors/bullet/bullet.png","0,",8,8,0,-8,1,true)
   HoldPistol:AddAnimation(bullet)
   Caller:AddAction(HoldPistol)

   local callerPosition=Caller:GetPosition()
   Caller:SetPosition(callerPosition.X,callerPosition.Y,120)
   Caller.CollisionDimensions.Z=3
   Caller.CollisionDimensions.X=8
   Caller.CollisionDimensions.Y=8
end
function TalkAction()
end