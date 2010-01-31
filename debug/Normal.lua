dofile("Lua/Base/Init.lua")
FrameRate=UI.CreateWindow(0,0,"FrameRate")
engine:AddWindow(FrameRate)
i=0
while quit~=Misc.QUIT do
   i=i+1
   FrameRate:SelectElement("lblRate").Special=""..i
   FrameRate:SelectElement("lblRate"):Reload()
   quit=engine:RunEngine()
   for i=0,TbfeLua.bullets.Length-1 do
      if TbfeLua.bullets[i]~=nil then
	 local currentPosition=TbfeLua.bullets[i]:GetPosition()
	 local coll=TbfeLua.bullets[i]:ChangePosition(TbfeLua.bullets[i]:GetDirection(),false)
	 local finalPosition=TbfeLua.bullets[i]:GetPosition()
	 if finalPosition.X==currentPosition.X and finalPosition.Y==currentPosition.Y then
	    if coll~=-2 and coll~=-1 then
	       if TBFE.GetActorByNum(coll)~=nil and TBFE.GetActorByNum(coll)~=TBFE.TBFE_Base_MainPlayer then
		  TBFE.GetActorByNum(coll):StartAction("Shot")
	       end
	    end	  
	    engine:RemoveActor(TbfeLua.bullets[i])
	    TbfeLua.bullets[i]=nil
	 end
      end
   end
end
OverMap=nil
engine=nil
Actor=nil
TBFE=nil
UI=nil
Map=nil
Misc=nil
collectgarbage()
collectgarbage()