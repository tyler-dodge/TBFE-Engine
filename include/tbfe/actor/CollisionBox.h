class CollisionBox;
#ifndef CollisionBox_L
#define CollisionBox_L
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/SdlFunctions.h"
#include <math.h>
//Warning it is not a good idea to have position_.X equal to 0
//set it to anything else otherwise atm stupidity happens
class CollisionBox
{
 private:
  PositionF position_;
  PositionF dimensions_;
  Quaternion rotation_;
  bool isEnabled_;
 public:
  CollisionBox(PositionF,PositionF);
  PositionF getDimensions();
  vector<PositionF> generatePoints(PositionF,PositionF);
  void setDimensions(float,float,float);
  bool checkLine(float,float,float,float,float,float,float,float);
  PositionF getPosition();
  void setPosition(float,float,float);
  PositionF getCenter();
  Quaternion getRotation();
  void setRotation(Quaternion);

  bool checkCollision(CollisionBox,PositionF,bool crossCheck=true);
  bool checkEnabled();
  void setEnabled(bool);
};
#endif
