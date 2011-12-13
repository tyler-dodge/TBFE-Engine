#include <boost/python.hpp>
#include "SDL/SDL.h"
#include <fstream>
#include <sstream>
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/StringConversion.h"
#include "tbfe/UI/Window.h"
#include "tbfe/UI/Element.h"
#include <vector>
//Element Types
#include "tbfe/UI/StatBar.h"
#include "tbfe/UI/Label.h"
#include "tbfe/UI/ImageBox.h"
#include "tbfe/UI/TextBox.h"
extern vector<WindowType> windowTypeList;
extern bool loadWindows(std::string);
extern void addWindowType(WindowType);
extern int getWindowType(std::string);
extern Window * createWindow(int X,int Y, std::string WindowTypeName);
extern void deleteWindowList();
extern bool debug;
extern int pyInterface;
