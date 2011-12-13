#include "tbfe/misc/StringConversion.h"
template <class T> 
std::string toString (const T& variable)
{
  std::stringstream tempStream;
  tempStream << variable;
  return tempStream.str();
};

std::string loadString(ifstream * source, string EndChar,char * foundChar)
{
  if (source==NULL)
    {
      return "";
    };
  char Point;
  bool foundEndChar=false;
  stringstream CurrentString;
  Point=source->get();
  while (!foundEndChar && Point!=-1)
    {
      for (int i=0;i<EndChar.length();i++)
	{
	  if (EndChar[i]==Point)
	    {
	      if (foundChar!=NULL)
		{
		  *foundChar=Point;
		};
	      foundEndChar=true;
	    };
	};
      if (!foundEndChar)
	{
	  CurrentString << Point;
	  Point=source->get();
	};
    };
  return CurrentString.str();
};
std::string loadString(ifstream * source, char endChar)
{
  char Point;
  bool foundEndChar=false;
  stringstream CurrentString;
  Point=source->get();
  while (Point!=-1)
    {
      if (Point==endChar)
	{
	  return CurrentString.str();
	};
      CurrentString << Point;
      Point=source->get();
    };
  return CurrentString.str();
};

std::string nextSet(string * source, char EndChar)
{
  char Point;
  stringstream CurrentString;
  for(int i=0;i<source->size();i++)
    {
      if (source->at(i)!=EndChar)
	{
	  CurrentString << source->at(i);
	}
      else
	{
	  *source=source->substr(i+1);
	  return CurrentString.str();
	};
    };
  return CurrentString.str();
};
char nextChar(string * source)
{
  char currentChar=source->at(0);
  *source=source->substr(1);
  return currentChar;
};
string replaceString(string source, string targetText,string replaceText)
{
  int targetLoc=source.find(targetText);
  if (targetLoc==string::npos)
    {
      return source;
    };
  source.erase(targetLoc,targetText.size());
  source.insert(targetLoc,replaceText.c_str());
  return source;
};
