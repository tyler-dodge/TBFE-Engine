Inventory={}
--Inventory.SourceWindow
--Inventory.SourceInventory
--Inventory.SourceSlot
--Inventory.SourceReload
function Inventory.SelectSlot(TargetWindow,TargetInventory,TargetSlot,TargetReload)
   --Sets Inventory.SourceWindow, SourceSlot to the Target
   ItemMenu.Visible=false
   if Inventory.SourceInventory:Get(Inventory.SourceSlot-1)==-1 then
      Inventory.SourceWindow:SelectElement("SelectBox").Visible=false
      TargetWindow:SelectElement("SelectBox").Visible=true
      NewPosition=TargetWindow:SelectElement("Slot"..TargetSlot).CurrentPosition
      TargetWindow:SelectElement("SelectBox").CurrentPosition=NewPosition

      Inventory.SourceWindow=TargetWindow
      Inventory.SourceSlot=TargetSlot
      Inventory.SourceInventory=TargetInventory
      Inventory.SourceReload=TargetReload
      return
   end
   if TargetInventory:Get(TargetSlot-1)==-1 then
      Inventory.SourceWindow:SelectElement("SelectBox").Visible=false
      TargetInventory:Add(Inventory.SourceInventory:Remove(Inventory.SourceSlot-1),TargetSlot-1)
      TargetReload()
      Inventory.SourceReload()
      Inventory.SourceReload=TargetReload
   elseif TargetWindow==Inventory.SourceWindow and TargetSlot==Inventory.SourceSlot then
      ItemMenu.Visible=true
      NewPosition=Misc.Position()
      NewPosition.X=TargetWindow.ScreenPosition.X+TargetWindow:SelectElement("Slot"..TargetSlot).CurrentPosition.X+30
      NewPosition.Y=TargetWindow.ScreenPosition.Y+TargetWindow:SelectElement("Slot"..TargetSlot).CurrentPosition.Y-70
      ItemMenu.ScreenPosition=NewPosition
   end
end
function Inventory.DropItem()
   Inventory.SourceInventory:Remove(Inventory.SourceSlot-1)
   ItemMenu.Visible=false
   Inventory.SourceReload()
end
function Inventory.UseItem()
   local UsedItem=Inventory.SourceInventory:Remove(Inventory.SourceSlot-1)
   --Turnip
   if UsedItem==1 then
      TbfeFile.SaveData.Data['Hunger']=TbfeFile.SaveData.Data['Hunger']+40
   end
   --egg
   if UsedItem==2 then
      TbfeFile.SaveData.Data['Hunger']=TbfeFile.SaveData.Data['Hunger']+60
   end
   ItemMenu.Visible=false
   Inventory.SourceReload()
end