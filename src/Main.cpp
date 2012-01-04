#include "Main.h"
using namespace std;
extern "C"
{
  void init_PyTbfe(void);
  void init_PyActor(void);
  void init_PyMap(void);
  void init_PyMisc(void);
};
int main(int argc,char* args[])
{
  if (argc!=4)
    {
      printf(PROPER_USAGE);
    }
  else 
    {
      string localDirectory(args[1]);
      if (localDirectory[localDirectory.size()-1]!='/')
	localDirectory.push_back('/');
      
      Py_Initialize();
      init_PyTbfe();
      init_PyActor();
      init_PyMap();
      init_PyMisc();
      stringstream initPython;
      initPython << "import sys;sys.path.append('" << localDirectory << "');";
      initPython << "sys.path.append('" << args[3] << "')";
      PyRun_SimpleString(initPython.str().c_str());
      initPython.str(string());
      initPython << localDirectory << args[2];
      const char * fileName=initPython.str().c_str();
      FILE * newFile=fopen(fileName,"r");
      PyRun_SimpleFile(newFile,fileName);
      Py_Finalize();
    }
  return 0;
};
