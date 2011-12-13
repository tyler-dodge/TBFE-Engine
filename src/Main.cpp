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
  void init_PyTbfe(void);
  void init_PyActor(void);
  void init_PyMap(void);
  void init_PyMisc(void);
  void init_PyUI(void);
};
int main(int argc,char* args[])
{
  Py_Initialize();
  init_PyTbfe();
  init_PyActor();
  init_PyMap();
  init_PyMisc();
  init_PyUI();
  FILE * newFile=fopen(args[1],"r");
  PyRun_SimpleString("import sys;sys.path.append('./')");
  PyRun_SimpleFile(newFile,args[1]);
  Py_Finalize();
  return 0;
};
