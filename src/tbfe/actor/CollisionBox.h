#ifndef CollisionBox_L
#define CollisionBox_L
#include "../misc/Structs.h"
#include <math.h>
class CollisionBox
{
 private:
  PositionF position_;
  PositionF dimensions_;
  PositionF rotation_;
 public:
  CollisionBox(PositionF,PositionF);
  PositionF getDimensions();
  vector<PositionF> generatePoints(PositionF,PositionF);
  void setDimensions(float,float,float);
  bool checkLine(float,float,float,float,float,float,float,float);
  float convertToAngle(float,float);
  PositionF getPosition();
  void setPosition(float,float,float);

  PositionF getRotation();
  void setRotation(float,float,float);

  PositionF applyRotations(PositionF);
  bool checkCollision(CollisionBox,PositionF,bool crossCheck=true);
};
#endif
