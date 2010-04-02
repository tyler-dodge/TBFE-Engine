#include "Console.h"
Console::Console()
{
  lines_.resize(0);
};
Console::~Console()
{
};
int Console::pyInterface_=0;
void Console::errorMessage(int ErrorNumber,string Item)
{
  stringstream Message;
  Message << "      Error " << ErrorNumber << ": ";
  switch (ErrorNumber)
    {
    case 0:
      Message << Item.c_str() << " failed to load";
      write(Message.str());
      break;
    case 1:
      Message << "File ended while loading " << Item.c_str();
      write(Message.str());
      break;      
    };
};
int Console::evalExpression(string expression)
{
  //not thread safe
  stringstream newData;
  newData << "Tbfe.Console.setPyInterface(" << expression << ")";
  PyRun_SimpleString(newData.str().c_str());
  return pyInterface_;
};
int Console::write(string text)
{
  lines_.push_back(text);
};
void Console::runLine(string Line)
{
  if (Line!="")
    {
      PyRun_SimpleString(Line.c_str());
    };
};
void Console::execute(string filename)
{ 
  FILE * newFile=fopen(filename.c_str(),"r");
  PyRun_SimpleFile(newFile,filename.c_str());
};
string Console::getLine(int lineNum)
{
  if (lineNum<lines_.size())
    {
      return lines_.at(lineNum);
    };
  return "";
};
int Console::getNumberOfLines()
{
  return lines_.size();
};
void Console::setPyInterface(int newNum)
{
  pyInterface_=newNum;
};
