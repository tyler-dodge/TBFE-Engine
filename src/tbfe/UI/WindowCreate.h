#include "SDL/SDL.h"
#include <fstream>
#include <sstream>
#include "../misc/Structs.h"
#include "../misc/StringConversion.h"
#include "Window.h"
#include "Element.h"
#include <vector>
//Element Types
#include "StatBar.h"
#include "Label.h"
#include "ImageBox.h"
extern vector<WindowType> windowTypeList;
extern bool loadWindows(std::string);
extern void addWindowType(WindowType);
extern int getWindowType(std::string);
extern Window * createWindow(int X,int Y, std::string WindowTypeName);
extern void deleteWindowList();
extern bool debug;
extern int pyInterface;
