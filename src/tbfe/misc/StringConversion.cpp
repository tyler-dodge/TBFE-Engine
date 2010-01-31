#include "StringConversion.h"
template <class T> 
inline std::string toString (const T& variable)
{
  std::stringstream tempStream;
  tempStream << variable;
  return tempStream.str();
};

std::string loadString(ifstream * source, char EndChar)
{
  char Point;
  stringstream CurrentString;
  Point=source->get();
  while (Point!=EndChar && Point!=-1)
    {
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
