Test=Actor.CreateActor(-1000,-1000,"Narrator","Npc")
Door=Actor.CreateActor(1300,1400,"door","door")
AngryGuy=Actor.CreateActor(1300,1000,"Git outta mah hawse!!!!","Npc","Angry Guy")
AngryGuy.CurrentAI=Misc.STANDING
engine:AddActor(Test)
engine:AddActor(Door)
engine:AddActor(AngryGuy)