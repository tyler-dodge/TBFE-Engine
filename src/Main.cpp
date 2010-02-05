#ifndef LUA_L
#define LUA_L
#endif
#include <Python.h>
#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;
extern "C"
{
  void init_TBFE(void);
  void init_Actor(void);
  void init_Map(void);
  void init_Misc(void);
  void init_UI(void);
};
int main(int argc,char* args[])
{
  Py_Initialize();
  init_TBFE();
  init_Actor();
  init_Map();
  init_Misc();
  init_UI();
  FILE * newFile=fopen(args[1],"r");
  PyRun_SimpleFile(newFile,args[1]);
  Py_Finalize();
  return 0;
};
