
#ifndef Console_L
#define Console_L
#define CONSOLE_WRITE(line) \
  Console::Instance()->write((line))
#define CONSOLE_RUN(line) \
  Console::Instance()->runLine((line))
#define CONSOLE_EVAL(line) \
  Console::Instance()->evalExpression((line))
#define CONSOLE_RUN_FILE(fileName) \
  Console::Instance()->execute((fileName))
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
  Console();
  ~Console();
  static Console console;
 public:
  static Console * Instance();
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
