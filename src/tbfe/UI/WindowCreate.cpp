#include "WindowCreate.h"

vector<WindowType> windowTypeList;
vector<Window *> CreatedWindowList;
bool debug;
int pyInterface=0;
int evalExpression(string expression)
{
  stringstream newData;
  newData << "UI.cvar.pyInterface=" << expression;
  PyRun_SimpleString(newData.str().c_str());
  return pyInterface;
};
bool loadWindows(std::string FileName)
{ 

  ifstream WindowData(FileName.c_str(),ifstream::binary);
  if (WindowData==NULL)
    {      
      cout << FileName << " failed to load\n";
      TBFE_Base::MainConsole.errorMessage(0,FileName);
      return false;
    };
  bool EndLoop=false;
  int i=0;
  while (i<100)
    {
      i++;
      WindowType NewWindow;
      NewWindow.Name=loadString(&WindowData,':');
      if (NewWindow.Name=="")
	{	   
	  return true;
	}
      string Data;
      Data=loadString(&WindowData,'(');
      if (Data=="")
	{
	  TBFE_Base::MainConsole.errorMessage(1,FileName);
	  if (debug)
	    {
	      cout << NewWindow.Name << "Failed at (\n";
	    };
	  return false;
	};
      int ElementNumber=atoi(Data.c_str());

      Data=loadString(&WindowData,',');
      if (Data=="")
	{
	  TBFE_Base::MainConsole.errorMessage(1,FileName); 
	  if (debug)
	    {
	      cout << NewWindow.Name << "Failed at Width\n";
	    };
	  return false;
	};
      NewWindow.Width=evalExpression(Data);
      
      Data=loadString(&WindowData,')');
      if (Data=="")
	{
	  TBFE_Base::MainConsole.errorMessage(1,FileName); 
	  if (debug)
	    {
	      cout << NewWindow.Name << "Failed at Height\n";
	    };
	  return false;
	};
      NewWindow.Height=evalExpression(Data);

      NewWindow.Elements.resize(ElementNumber); 
      for (int i=0;i<ElementNumber;i++)
	{
	  string ElementData;
	  loadString(&WindowData,';');
	  std::string ElementName;
	  std::string ElementSpecial;
	  Position ElementPosition;
	  
	  ElementData=loadString(&WindowData,':');
	  if (ElementData=="")
	    {
	      TBFE_Base::MainConsole.errorMessage(1,FileName+".Name");
	      if (debug)
		{
		  cout << NewWindow.Name << "Failed at Element " << i << ":Name"<< "\n";
		};
	      return false;
	    };
	  NewWindow.Elements[i].Name=ElementData;
	  
	  ElementData=loadString(&WindowData,'(');
	  if (ElementData=="")
	    {
	      TBFE_Base::MainConsole.errorMessage(1,FileName+".Name"); 	   
	      if (debug)
		{
		  cout << NewWindow.Name << "Failed at Element " << i << ":Name"<< "\n";
		};
	      return false;
	    };
	  NewWindow.Elements[i].Type=ElementData;

	  ElementData=loadString(&WindowData,',');
	  if (ElementData=="")
	    {
	      TBFE_Base::MainConsole.errorMessage(1,FileName+".Type"); 	      
	      if (debug)
		{
		  cout << NewWindow.Name << "Failed at Element " << i << ":Type" << "\n";
		};
	      return false;
	    };
	  NewWindow.Elements[i].ElementPosition.X=evalExpression(ElementData);
	  
	  ElementData=loadString(&WindowData,')');
	  if (ElementData=="")
	    {
	      TBFE_Base::MainConsole.errorMessage(1,FileName+".ElementPosition.X"); 	      
	      if (debug)
		{
		  cout << NewWindow.Name << "Failed at Element " << i << ":ElementPosition.X" << "\n";
		};
	      return false;
	    };
	  NewWindow.Elements[i].ElementPosition.Y=evalExpression(ElementData);
	  
	  ElementData=loadString(&WindowData,',');
	  NewWindow.Elements[i].Special=ElementData;
	}; 
      loadString(&WindowData,'\n');
      addWindowType(NewWindow);
    };
};
void addWindowType(WindowType NewType)
{
  windowTypeList.push_back(NewType);
};
int getWindowType(std::string WindowName)
{
  for (int i=0;i<windowTypeList.size();i++)
    {
      if (windowTypeList.at(i).Name==WindowName)
	{
	  return i;
	};
    };
  return -1;
};
Window * createWindow(int X,int Y, std::string WindowTypeName)
{
  std::stringstream ConsoleWrite;
  Window * TempWindow;
  SDL_Color ColorKey;
  ColorKey.r=0;
  ColorKey.g=255;
  ColorKey.b=0;
  int WindowTypeNum;
  WindowTypeNum=getWindowType(WindowTypeName);
  if (WindowTypeNum==-1)
    {
      return NULL;
    };
  TempWindow=new Window(windowTypeList.at(WindowTypeNum).Width,windowTypeList.at(WindowTypeNum).Height,X,Y);
  for (int i=0;i<windowTypeList[WindowTypeNum].Elements.size();i++)
    {
      Element * NewElement;
      std::string Type=windowTypeList[WindowTypeNum].Elements[i].Type;
      if (Type=="StatBar")
	{
	  NewElement=new StatBar(windowTypeList[WindowTypeNum].Elements[i].ElementPosition.X,
				 windowTypeList[WindowTypeNum].Elements[i].ElementPosition.Y,
				 windowTypeList[WindowTypeNum].Elements[i].Special);
	};
      if (Type=="Label")
	{
	  NewElement=new Label(windowTypeList[WindowTypeNum].Elements[i].ElementPosition.X,
			       windowTypeList[WindowTypeNum].Elements[i].ElementPosition.Y,
			       windowTypeList[WindowTypeNum].Elements[i].Special);
	};
      if (Type=="ImageBox")
	{
	  NewElement=new ImageBox(windowTypeList[WindowTypeNum].Elements[i].ElementPosition.X,
				  windowTypeList[WindowTypeNum].Elements[i].ElementPosition.Y,
				  windowTypeList[WindowTypeNum].Elements[i].Special);
	};
      if (NewElement!=NULL)
	{
	  NewElement->setName(windowTypeList[WindowTypeNum].Elements[i].Name);
	  TempWindow->addElement(NewElement);
	};
    };
  CreatedWindowList.push_back(TempWindow);
  return TempWindow;
};
void deleteWindowList()
{
  for (int i=0;i<CreatedWindowList.size();i++)
    {
      delete CreatedWindowList.at(i);
    };
  CreatedWindowList.resize(0);
};
