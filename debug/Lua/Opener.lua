function TitleScreen()
   Action="None"
   engine:SelectEvent("GameMenu").Enabled=false
   while quit~=Misc.QUIT and Action=="None" do
      
      TbfeLua.NormalEngineLoop()
      if GameMenu~=nil then
	 GameMenu.Visible=false
      end
   end
   engine:SelectEvent("GameMenu").Enabled=true
end
function ChangeSelect(position)
   LoadWindow:SelectElement("Selected").CurrentPosition.Y=(position)*30
end
TitleText=UI.CreateWindow(0,0,"TitleScreen")
engine:AddWindow(TitleText)
engine:AddEvent("New Game",TitleText:SelectElement("picNew"),TitleText,"Action='New'",Misc.CLICK)
engine:AddEvent("Load Game",TitleText:SelectElement("picLoadGame"),
		TitleText,"Action='Load'",Misc.CLICK)
engine:AddEvent("Options",TitleText:SelectElement("picOptions"),
		TitleText,"Action='Options'",Misc.CLICK)
engine:AddEvent("Credits",TitleText:SelectElement("picCredits"),
		TitleText,"Action='Credits'",Misc.CLICK)
engine:AddEvent("Quit",TitleText:SelectElement("picQuit"),TitleText,"engine.Logic.quit=true",Misc.CLICK)
TBFE.TBFE_Base_KeyControl=false
Action="Title"
while Action=="Title" and quit~=Misc.QUIT do
   TitleText.Visible=true
   TitleScreen()
   if Action=="Load" then
      UiLua.ShowLoadWindow()
      LoadWindow.Visible=true
      TitleScreen()
      LoadWindow.Visible=false
   end
   if Action=="New" then
      TitleText.Visible=false
   end
end
TBFE.TBFE_Base_KeyControl=true