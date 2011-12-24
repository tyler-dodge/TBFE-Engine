#ifndef Camera_L
#define Camera_L
#include "tbfe/misc/Position.h"
class Camera
{
 private:
  PositionF offset;
  PositionF followOffset;
  Quaternion angle;
 public:
  Camera(PositionF,PositionF,Quaternion);
  Camera();
  PositionF getOffset();
  PositionF getFollowOffset();
  Quaternion getAngle();
};
#endif
