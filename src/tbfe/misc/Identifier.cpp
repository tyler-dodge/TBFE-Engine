#include "tbfe/misc/Identifier.h"
int Identifier::nextId=FIRST_ID;
Identifier::Identifier()
{
  thisId=nextId++;
}
int Identifier::getId()
{
  return thisId;
}
bool Identifier::operator<(Identifier * id)
{
  return thisId<id->getId();
}
