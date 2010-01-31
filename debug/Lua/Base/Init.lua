--Initializing Engine
engine=TBFE.TBFE()
C=TBFE.TBFE_Base_MainConsole
dofile("Lua/Base/Tbfe.lua")
UI.Debug=true
Actor.LoadActors("Data/Types/Actor.cfg")
UI.LoadWindows("Data/Types/Window.cfg")
TBFE.TBFE_Base_CurrentMap:LoadPlants("Data/Types/Plant.cfg")
quit=5
engine:AddWindow(FrameRate)
engine:ChangeMap("Maps/farm.fmm");
engine.RenderWindow:InitializeTileSets()
playerParts={}
playerParts['head']="Actors/living/head/"
playerParts['torso']="Actors/living/torso/white_tshirt/"
playerParts['legs']="Actors/living/legs/jeans/"
playerParts['body']="Actors/living/body/normal/"

head=Actor.Animation(playerParts['head'].."head.png","0,",100,200,-30,-140,1,true)
torso=Actor.Animation(playerParts['torso'].."pistol.png","9,",300,250,-130,-190,1,true)
legs=Actor.Animation(playerParts['legs'].."pistol.png","9,",300,250,-130,-190,1,true)
body=Actor.Animation(playerParts['body'].."pistol.png","9,",300,250,-130,-190,1,true)
pistol=Actor.Animation("Actors/living/pistol/pistol.png","9,",300,250,-130,-190,1,true)
HoldPistol=Actor.Action("pistol","")
HoldPistol:AddAnimation(head)
HoldPistol:AddAnimation(body)
HoldPistol:AddAnimation(legs)
HoldPistol:AddAnimation(torso)
HoldPistol:AddAnimation(pistol)
HoldPistol:SetMainAnimation(1)
TBFE.TBFE_Base_MainPlayer:AddAction(HoldPistol)

head=Actor.Animation(playerParts['head'].."head.png","0,",100,200,-30,-140,1,true)
local anim="0,1,2,3,4,5,6,7,8,9,"
torso=Actor.Animation(playerParts['torso'].."pistol.png",anim,300,250,-130,-190,1,false)
legs=Actor.Animation(playerParts['legs'].."pistol.png",anim,300,250,-130,-190,1,false)
body=Actor.Animation(playerParts['body'].."pistol.png",anim,300,250,-130,-190,1,false)
pistol=Actor.Animation("Actors/living/pistol/pistol.png",anim,300,250,-130,-190,1,false)
HoldPistol=Actor.Action("holdPistol","")
HoldPistol:AddAnimation(head)
HoldPistol:AddAnimation(body)
HoldPistol:AddAnimation(legs)
HoldPistol:AddAnimation(torso)
HoldPistol:AddAnimation(pistol)
HoldPistol:SetMainAnimation(1)
TBFE.TBFE_Base_MainPlayer:AddAction(HoldPistol)
local anim="0,1,2,3,4,5,6,7,8,9,"
head=Actor.Animation(playerParts['head'].."head.png","0,",100,200,-30,-140,1,true)
torso=Actor.Animation(playerParts['torso'].."pistol.png","9,",300,250,-130,-190,1,true)
legs=Actor.Animation(playerParts['legs'].."pistol.png","9,",300,250,-130,-190,1,true)
body=Actor.Animation(playerParts['body'].."pistol.png","9,",300,250,-130,-190,1,true)
pistol=Actor.Animation("Actors/living/pistol/shoot.png",anim,300,250,-130,-190,1,false)
HoldPistol=Actor.Action("shootPistol","")
HoldPistol:AddAnimation(head)
HoldPistol:AddAnimation(body)
HoldPistol:AddAnimation(legs)
HoldPistol:AddAnimation(torso)
HoldPistol:AddAnimation(pistol)
HoldPistol:SetMainAnimation(4)
TBFE.TBFE_Base_MainPlayer:AddAction(HoldPistol)
--animParams=",0,1,(300,250;-130,-190)0,-1|"
--animData=      playerParts['head'].."head.png"..",1,1,(100,200;-30,-140)0,-1|0:"
--animData=animData..playerParts['body'].."pistol.png"..animParams.."0,1,2,3,4,5,6,7,8,9,10:"
--animData=animData..playerParts['legs'].."pistol.png"..animParams.."-1:"
--animData=animData..playerParts['torso'].."pistol.png"..animParams.."0,1,2,3,4,5,6,7,8,9,10:"
--animData=animData.."Actors/living/pistol/pistol.png,0,1,(300,250;-130,-190)0,-1|0,1,2,3,4,5,6,7,8,9,10:"
--TBFE.TBFE_Base_MainPlayer:AddAction(TBFE.TBFE_Base_MainPlayer:CreateAction("holdPistol",animData,4,""))
--animParams=",0,1,(300,250;-130,-190)0,-1|"
--animData=      playerParts['head'].."head.png"..",1,1,(100,200;-30,-140)0,-1|0:"
--animData=animData..playerParts['body'].."pistol.png"..animParams.."-1:"
--animData=animData..playerParts['legs'].."pistol.png"..animParams.."-1:"
--animData=animData..playerParts['torso'].."pistol.png"..animParams.."-1:"
--animData=animData.."Actors/living/pistol/pistol.png,0,1,(300,250;-130,-190)0,-1|10,9,8,7,6,5,4,3,2,1,0:"
--TBFE.TBFE_Base_MainPlayer:AddAction(TBFE.TBFE_Base_MainPlayer:CreateAction("holsterPistol",animData,4,""))
--animParams=",1,1,(300,250;-130,-190)0,-1|"
--animData=      playerParts['head'].."head.png"..",1,1,(100,200;-30,-140)0,-1|0:"
--animData=animData..playerParts['body'].."pistol.png"..animParams.."9:"
--animData=animData..playerParts['legs'].."pistol.png"..animParams.."9:"
--animData=animData..playerParts['torso'].."pistol.png"..animParams.."9:"
--animData=animData.."Actors/living/pistol/shoot.png,0,1,(300,250;-130,-190)0,-1|0,1,2,3,4,5,6,7,8,9,10:"
--TBFE.TBFE_Base_MainPlayer:AddAction(TBFE.TBFE_Base_MainPlayer:CreateAction("shootPistol",animData,4,""))
--TBFE.TBFE_Base_MainPlayer:LoadActions()
engine:AddGlobalEvent("GameMenu",Misc.KEYPRESS,27,"engine.Logic.quit=true")