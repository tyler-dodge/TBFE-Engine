function UpdateConversation()
   Conversation.Window:SelectElement("Conversation").special=Conversation.Text
   for i,0,Conversation.ResponseLength do
      Conversation.Window:SelectElement("Response"..i).special=Conversation.Response[i]
      Conversation.Window:Reload()
   end
end
if Conversation==nil then
   Conversation={}
   Conversation.Text=""
   Conversation.Responses={}
   Conversation.ResponseFunctions={}
   Conversation.ResponseLength=0
   Conversation.Window=UI.CreateWindow(100,SCREEN_HEIGHT-300,"ConversationWindow")
   engine:AddWindow(Conversation.Window)
end