#ifndef Console_L
#define Console_L
#include <boost/python.hpp>
#include <iostream>
#include <sstream>
#include <Python.h>
#include <vector>
using namespace std;
class Console
{
 private:
  vector<string> lines_;
  static int pyInterface_;
 public:
  Console();
  ~Console();
  int write(string);
  void errorMessage(int,string);
  int evalExpression(string);
  void runLine(string);
  void execute(string);
  string getLine(int);
  int getNumberOfLines();
  static void setPyInterface(int);
};
#endif
