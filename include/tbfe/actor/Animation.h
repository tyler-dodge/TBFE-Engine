class Animation;
#ifndef Animation_L
#define Animation_L
#include "tbfe/misc/StringConversion.h"
#include "tbfe/misc/Structs.h"
#include "tbfe/raster/Model.h"
class Animation
{
 private:
  vector<int> frames_;
  Model model_;
  PositionF offset_;
  Quaternion rotation_;
  float rate_;
  bool loop_;
  int finalFrame_;
  float currentFrame_;
 public:
  Animation();
  Animation(string,string,float OffsetX=0, float OffsetY=0,float fps=1,
	    bool doesLoop=false,int FinalFrame=-1);
  int getFrame();
  bool currentFramePlus();
  bool loadModel();
  void setModelSource(string);
  Model getModel();
  void reset();
  float getCurrentFrame();
  void setCurrentFrame(float);
  

  bool getLoop();
  void setLoop(bool);


  int getFinalFrame();
  void setFinalFrame(int);
  
  PositionF getOffset();
  void setOffset(float,float,float z=0);
  Quaternion getRotation();
  void rotate(Quaternion);
  void setRotation(Quaternion);
  
  float getRate();
  void setRate(float);
};
#endif
