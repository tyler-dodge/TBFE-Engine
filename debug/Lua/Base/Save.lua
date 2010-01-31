TbfeFile={}
function TbfeFile.NextSet(Text,Character)
   local foundChar=string.find(Text,Character)
   Text=string.reverse(Text)
   local StartString=string.reverse(string.sub(Text,-1*(foundChar-1)))
   local EndString=string.sub(string.reverse(Text),foundChar+1)
   return StartString,EndString
end
function TbfeFile.LoadOptions()
   local OptionsFile=io.open("Options.cfg")
   local Data=OptionsFile:read()
   local loss
   loss,Data=TbfeFile.NextSet(Data,':')
   TBFE.TBFE_Render_SCREEN_WIDTH,Data=TbfeFile.NextSet(Data,',')
   Data=OptionsFile:read()
   loss,Data=TbfeFile.NextSet(Data,':')
   TBFE.TBFE_Render_SCREEN_HEIGHT,Data=TbfeFile.NextSet(Data,',')
   engine.RenderWindow:Init()
end