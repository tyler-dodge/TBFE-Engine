#ifndef Console_L
#define Console_L
#include <iostream>
#include <sstream>
using namespace std;
class Console
{
 private:
  vector<string> lines_;
 public:
  Console();
  ~Console();
  int write(string);
  void errorMessage(int,string);
  void runLine(string);
  void execute(string);
  string getLine(int);
  int getNumberOfLines();
};
#endif
