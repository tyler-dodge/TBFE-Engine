function NewMap(width,height,farmable)
TBFE.TBFE_Base_CurrentMap:GenerateMap(width,height,farmable)
engine.RenderWindow:InitializeTileSets()
end
function ChangeMap(Name)
   engine:ChangeMap(Name)
   engine.RenderWindow:InitializeTileSets()
end
function TileSetMouse()
   TileSetList:SelectElement("cursor").CurrentPosition=engine.Cursor
end
function SaveMap(Name)
   TBFE.TBFE_Base_CurrentMap:DumpMap(Name)
end
engine=MapEditor.MapEditor()
engine:ChangeMap("Maps/farm.fmm");
UI.LoadWindows("Data/Types/Window.cfg")
Info=UI.CreateWindow(210,TBFE.TBFE_Render_SCREEN_HEIGHT-50,"MapEditorInfo")
engine:AddWindow(Info)
engine.RenderWindow:InitializeTileSets();
Actor.LoadActors("ActorTypes.cfg")
quit=5
DoTutorial=false
while quit==5 do
   Info:SelectElement("lblText").Special="Cursor Position: ("..((engine.Cursor.X+engine.MapX)/100)..","..((engine.Cursor.Y+engine.MapY)/100).."), Layer:"..engine.Layer..", Show Foreground:"..tostring(engine.RenderWindow.ShowForeground)
   Info:SelectElement("lblText"):Reload()
   quit=engine:EditorLoop()
end