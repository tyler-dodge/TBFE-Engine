function StartAction()
   head=Actor.Animation("Actors/living/head/head.png","0,",100,200,-30,-140,1,false)
   HoldPistol=Actor.Action("Shot","engine:RemoveActor(Caller)")
   HoldPistol:AddAnimation(head)
   HoldPistol:SetMainAnimation(0)
   TBFE.TBFE_Base_MainPlayer:AddAction(HoldPistol)
end
function TalkAction()
end