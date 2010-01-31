TbfeLua={}
SaveData={}
function TbfeLua.HoldGun()
   if TBFE.TBFE_Base_MainPlayer.BaseAction=="pistol" then
      TBFE.TBFE_Base_MainPlayer.BaseAction="Walk"
      TBFE.TBFE_Base_MainPlayer:StartAction("holsterPistol")
      return
   end
   TBFE.TBFE_Base_MainPlayer.BaseAction="pistol"
   TBFE.TBFE_Base_MainPlayer:StartAction("holdPistol")
end
function TbfeLua.ShootGun()
   if TBFE.TBFE_Base_MainPlayer.BaseAction=="pistol" and TBFE.TBFE_Base_MainPlayer:GetCurrentAction():GetName()=="None" then
      TBFE.TBFE_Base_MainPlayer:EndCurrentAction()
      TBFE.TBFE_Base_MainPlayer:StartAction("shootPistol")
      TbfeLua.Bullet()
      return
   end
end
function TbfeLua.Bullet()
   local position=TBFE.TBFE_Base_MainPlayer:GetPosition()
   local bulletDirection=TBFE.TBFE_Base_MainPlayer:GetDirection()
   local bulletOffset=Misc.Position()
   if bulletDirection==Misc.RIGHT then
      bulletOffset.X=85
      bulletOffset.Y=5
   elseif bulletDirection==Misc.LEFT then
      bulletOffset.X=-50
      bulletOffset.Y=15
   elseif bulletDirection==Misc.DOWN then
      bulletOffset.X=15
      bulletOffset.Y=60
   elseif bulletDirection==Misc.UP then
      bulletOffset.X=15
      bulletOffset.Y=-40
   end
   TbfeLua.bullets[TbfeLua.bullets.Length]=Actor.CreateActor(position.X+bulletOffset.X,position.Y+bulletOffset.Y,"bullet","bullet")
   TbfeLua.bullets[TbfeLua.bullets.Length]:SetDirection(TBFE.TBFE_Base_MainPlayer:GetDirection())
   engine:AddActor(TbfeLua.bullets[TbfeLua.bullets.Length])
   TbfeLua.bullets.Length=TbfeLua.bullets.Length+1
end
TbfeLua.bullets={}
TbfeLua.bullets.Length=0
engine:AddGlobalEvent("HoldGun",Misc.KEYPRESS,32,"TbfeLua.HoldGun();")
engine:AddGlobalEvent("ShootGun",Misc.KEYPRESS,306,"TbfeLua.ShootGun();")