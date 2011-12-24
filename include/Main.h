#ifndef Main_L
#define Main_L
#include <Python.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <exception>
#define PROPER_USAGE "Proper Usage: Tbfe LocalDirectory StartUp.py (relative to LocalDirectory) PythonLibs\n"
extern "C"
{
  void init_PyTbfe(void);
  void init_PyActor(void);
  void init_PyMap(void);
  void init_PyMisc(void);
  void init_PyUI(void);
};
int main(int argc,char* args[]);
#endif
