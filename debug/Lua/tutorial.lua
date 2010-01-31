ScriptedConversation("welcome to Agrarious",Test)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("Act I: Scene 1",Test)
for i=0,400,1 do
engine:RunEngine()
Bob:ChangePosition(TBFE.LEFT,engine.CurrentMap,true)
end
ScriptedConversation("The Overdrawn Tutorial",Test)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("Well, I am here to showcase the various actions available to you in Agrarious",Bob)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("To be honest, I can't actually...Embarrassing thing, the programmer wrote me in a different",Bob)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("class than the player class...Really kinda stupid. Anyway, press the spacebar to use tools",Bob)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("However, I am afraid you can only use the tools on that dirt over there.",Bob)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("Press the Q button to switch between tools",Bob)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("You can see which tool you have by looking at that number in the bottom left",Bob)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("0 is a hoe, 1 is seeds, and 2 is a watering can.",Bob)
while engine.KeyControl==false do
engine:RunEngine()
end
ScriptedConversation("Well, I have to go do nothing! I was only here to showcase the new scripting engine",Bob)