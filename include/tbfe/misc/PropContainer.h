#ifndef PropContainer_L
#define PropContainer_L
#include<string>
#include<map>
#include"tbfe/misc/Identifier.h"
class PropContainer : public Identifier, private std::map<std::string,std::string>
{
 public:
  std::string getProperty(std::string);
  void setProperty(std::string,std::string);
};
#endif
