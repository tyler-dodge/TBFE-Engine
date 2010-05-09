#ifndef StringConv_L
#define StringConv_L
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
template <class T> extern std::string toString (const T&);
extern std::string loadString(ifstream *, string,char * foundChar=NULL);
extern std::string loadString(ifstream *, char);
extern std::string nextSet(string *,char);
extern char nextChar(string *);
extern std::string replaceString(string, string,string);
#endif

