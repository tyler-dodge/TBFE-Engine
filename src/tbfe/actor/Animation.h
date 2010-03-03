#ifndef Animation_L
#define Animation_L
#include "../misc/Structs.h"
class Animation
{
 private:
  vector<int> frames_;
  Model model_;
  PositionF offset_;
  PositionF rotation_;
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
  aiScene * getModel();
  void reset();
  float getCurrentFrame();
  void setCurrentFrame(float);
  

  bool getLoop();
  void setLoop(bool);


  int getFinalFrame();
  void setFinalFrame(int);
  
  PositionF getOffset();
  void setOffset(float,float,float z=0);
  PositionF getRotation();
  void setRotation(float,float,float);

  
  float getRate();
  void setRate(float);
};
#endif
