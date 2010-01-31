TbfeFile={}
function TbfeFile.CreateSaveData()
   TbfeFile.SaveData={}
   TbfeFile.SaveData.Pointers={}
   TbfeFile.SaveData.Length=0
   TbfeFile.SaveData.Data={}
end
function TbfeFile.NextSet(Text,Character)
   local foundChar=string.find(Text,Character)
   Text=string.reverse(Text)
   local StartString=string.reverse(string.sub(Text,-1*(foundChar-1)))
   local EndString=string.sub(string.reverse(Text),foundChar+1)
   return StartString,EndString
end

function TbfeFile.AddEntry(tag,data)
   TbfeFile.SaveData.Data[tag]=data
   TbfeFile.SaveData.Pointers[TbfeFile.SaveData.Length]=tag
   TbfeFile.SaveData.Length=TbfeFile.SaveData.Length+1
end
function TbfeFile.SaveGame(name)
   local file=io.open(name..".dat","rb")
   if file~=nil then
      file=io.open(name..".dat","wb")
   else
      engine:CreateFile(name..".dat")
      file=io.open(name..".dat","wb")
      local SaveLocations=io.open("Data/SaveLocations.cfg","a+")
      SaveLocations:write(name.."\n")
      SaveLocations:close()
   end
   for i=0,TbfeFile.SaveData.Length-1,1 do
      file:write(""..TbfeFile.SaveData.Pointers[i]..";")
      local DataType
      if type(TbfeFile.SaveData.Data[TbfeFile.SaveData.Pointers[i]])=="string" then
	 DataType="S"
      else
	 DataType="N"
      end
      file:write(DataType)
      file:write(":"..TbfeFile.SaveData.Data[TbfeFile.SaveData.Pointers[i]]..",")
      file:write("\n")
   end
   file:close()
end
function TbfeFile.LoadGame(name)
   TbfeFile.CreateSaveData()
   local file=io.open(name..".dat","rb")
   local EndOfFile=false
   if file==nil then
      TBFE.TBFE_Base_MainConsole:Write(name..".dat")
   end
   while EndOfFile==false do
      fileData=file:read()  --has to be public in order to do Call
      if Interpreter.Call("PointerName,fileData=TbfeFile.NextSet(fileData,';')")==false then
	 return
      end
      if PointerName=="" then
	 return
      end
      if Interpreter.Call("DataType,fileData=TbfeFile.NextSet(fileData,':')")==false then
	 return
      end
      if Interpreter.Call('Data,fileData=TbfeFile.NextSet(fileData,",")')==false then
	 return
      end
      if Data=="" then
	 return
      end
      if DataType=="N" then
	 Data=tonumber(Data)
      end
      Interpreter.Call('Loss,fileData=TbfeFile.NextSet(fileData,"\n")')
      TbfeFile.SaveData.Data[PointerName]=Data
      TbfeFile.SaveData.Pointers[TbfeFile.SaveData.Length]=PointerName
      TbfeFile.SaveData.Length=TbfeFile.SaveData.Length+1      
   end
end
function TbfeFile.LoadOptions()
   local OptionsFile=io.open("Data/Options.cfg")
   local Data=OptionsFile:read()
   local loss
   loss,Data=TbfeFile.NextSet(Data,':')
   TBFE.TBFE_Render_SCREEN_WIDTH,Data=TbfeFile.NextSet(Data,',')
   Data=OptionsFile:read()
   loss,Data=TbfeFile.NextSet(Data,':')
   TBFE.TBFE_Render_SCREEN_HEIGHT,Data=TbfeFile.NextSet(Data,',')
   engine.RenderWindow:Init()
end