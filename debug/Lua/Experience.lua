function AddPoint(tag)
   TbfeFile.SaveData.Data[tag]=TbfeFile.SaveData.Data[tag]+1
   TbfeFile.SaveData.Data['Experience']=TbfeFile.SaveData.Data['Experience']-1
   UpdateExperience()
end
function UpdateExperience()
   if TbfeFile.SaveData.Data['Strength']==nil then
      TbfeFile.AddEntry("Strength",6)
   end
   if TbfeFile.SaveData.Data['Endurance']==nil then
      TbfeFile.AddEntry("Endurance",6)
   end
   if TbfeFile.SaveData.Data['Intellect']==nil then
      TbfeFile.AddEntry("Intellect",6)
   end
   if TbfeFile.SaveData.Data['Charisma']==nil then
      TbfeFile.AddEntry("Charisma",6)
   end
   if TbfeFile.SaveData.Data['Experience']==nil then
      TbfeFile.AddEntry("Experience",0)
   end
   if TbfeFile.SaveData.Data['ExperienceLevel']==nil then
      TbfeFile.AddEntry("ExperienceLevel",0)
   end
   ExperienceWindow:SelectElement("StrengthValue").Special=TbfeFile.SaveData.Data['Strength']
   ExperienceWindow:SelectElement("EnduranceValue").Special=TbfeFile.SaveData.Data['Endurance']
   ExperienceWindow:SelectElement("IntellectValue").Special=TbfeFile.SaveData.Data['Intellect']
   ExperienceWindow:SelectElement("CharismaValue").Special=TbfeFile.SaveData.Data['Charisma']
   ExperienceWindow:SelectElement("RemainingValue").Special=TbfeFile.SaveData.Data['Experience']
   
   ExperienceWindow:SelectElement("StrengthValue"):Reload()
   ExperienceWindow:SelectElement("EnduranceValue"):Reload()
   ExperienceWindow:SelectElement("IntellectValue"):Reload()
   ExperienceWindow:SelectElement("CharismaValue"):Reload()   
   ExperienceWindow:SelectElement("RemainingValue"):Reload()
   if TbfeFile.SaveData.Data['Experience']==0 then
      ExperienceWindow:SelectElement("StrengthPlus").Visible=false
      ExperienceWindow:SelectElement("EndurancePlus").Visible=false
      ExperienceWindow:SelectElement("IntellectPlus").Visible=false
      ExperienceWindow:SelectElement("CharismaPlus").Visible=false
      ExperienceWindow:SelectElement("RemainingValue").Visible=false
      ExperienceWindow:SelectElement("lblRemaining").Visible=false
   else
      ExperienceWindow:SelectElement("StrengthPlus").Visible=true
      ExperienceWindow:SelectElement("EndurancePlus").Visible=true
      ExperienceWindow:SelectElement("IntellectPlus").Visible=true
      ExperienceWindow:SelectElement("CharismaPlus").Visible=true
      ExperienceWindow:SelectElement("RemainingValue").Visible=true
      ExperienceWindow:SelectElement("lblRemaining").Visible=true      
   end
   local CurrentLevel=nil
   local i=0
   while CurrentLevel==nil do
      i=i+1
      if NextLevel[i]>TbfeFile.SaveData.Data['ExperienceLevel'] then
	 CurrentLevel=i
      end
   end
   if TbfeFile.SaveData.Data['Level']==nil then
      
      TbfeFile.AddEntry("Level",CurrentLevel)
   end
   ExperienceWindow:SelectElement("NextLevel").Special=NextLevel[CurrentLevel]-TbfeFile.SaveData.Data['ExperienceLevel']
   ExperienceWindow:SelectElement("NextLevel"):Reload()
   local PreviousLevel=0
   if CurrentLevel-1>0 then
      PreviousLevel=NextLevel[CurrentLevel-1]
   end
   Stats:SelectElement("ExperienceStats").Special=100-(NextLevel[CurrentLevel]-TbfeFile.SaveData.Data['ExperienceLevel'])/(NextLevel[CurrentLevel]-PreviousLevel)*100
end
if ExperienceWindow==nil then
   ExperienceWindow=UI.CreateWindow((TBFE.TBFE_Render_SCREEN_WIDTH-300)/2,(TBFE.TBFE_Render_SCREEN_HEIGHT-500)/2,"ExperienceWindow")
   engine:AddWindow(ExperienceWindow)
   engine:AddEvent("AddStrength",ExperienceWindow:SelectElement("StrengthPlus"),ExperienceWindow,"AddPoint('Strength')",Misc.CLICK)
   engine:AddEvent("AddEndurance",ExperienceWindow:SelectElement("EndurancePlus"),ExperienceWindow,"AddPoint('Endurance')",Misc.CLICK)
   engine:AddEvent("AddIntellect",ExperienceWindow:SelectElement("IntellectPlus"),ExperienceWindow,"AddPoint('Intellect')",Misc.CLICK)
   engine:AddEvent("AddCharisma",ExperienceWindow:SelectElement("CharismaPlus"),ExperienceWindow,"AddPoint('Charisma')",Misc.CLICK)
   engine:AddEvent("ExitExperience",ExperienceWindow:SelectElement("picClose"),ExperienceWindow,"ExperienceWindow.Visible=false",Misc.CLICK)
   UpdateExperience()
end