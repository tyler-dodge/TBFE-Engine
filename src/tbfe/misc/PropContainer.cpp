#include "tbfe/misc/PropContainer.h"

std::string PropContainer::getProperty(std::string name)
{
  return find(name)->second;
}
void PropContainer::setProperty(std::string name ,std::string value)
{
  (*this)[name]=value;
}
