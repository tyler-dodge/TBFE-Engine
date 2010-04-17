#ifndef CollisionBox_L
#define CollisionBox_L
#include "../misc/Structs.h"
#include <math.h>
//Warning it is not a good idea to have position_.X equal to 0
//set it to anything else otherwise atm stupidity happens
class CollisionBox
{
 private:
  PositionF position_;
  PositionF dimensions_;
  PositionF rotation_;
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
  PositionF getRotation();
  void setRotation(float,float,float);

  bool checkCollision(CollisionBox,PositionF,bool crossCheck=true);
  bool checkEnabled();
  void setEnabled(bool);
};
#endif
