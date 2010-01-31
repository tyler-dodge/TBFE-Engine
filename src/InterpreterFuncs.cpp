#include "InterpreterFuncs.h"
lua_State * L;
bool Call(string line)
{
  luaL_dostring(L,line.c_str());
  if(lua_gettop(L)==2)
    {
      return false;
    };
  return true;
};
