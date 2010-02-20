#ifndef Animation_L
#define Animation_L
#include "../misc/Structs.h"
class Animation
{
 private:
  vector<int> frames_;
  Model model_;
  Position dimensions_;
  Position offset_;
  int startX_;
  float rate_;
  bool loop_;
  int finalFrame_;
  float currentFrame_;
 public:
  Animation();
  Animation(string,string,int width=100,int height=200,int OffsetX=0, int OffsetY=0,float fps=1,
	    bool doesLoop=false,int StartX=0,int FinalFrame=-1);
  int getFrame();
  SDL_Rect getFrameRect(Direction);
  bool currentFramePlus();
  bool loadModel();
  void setModelSource(string);
  aiScene * getModel();
  void reset();
  float getCurrentFrame();
  void setCurrentFrame(float);
  
  Position getDimensions();
  void setDimensions(int,int);

  bool getLoop();
  void setLoop(bool);

  int getStartX();
  void setStartX(int);

  int getFinalFrame();
  void setFinalFrame(int);
  
  Position getOffset();
  void setOffset(int,int);
  
  float getRate();
  void setRate(float);
};
#endif
