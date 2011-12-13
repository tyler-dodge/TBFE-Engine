#include "tbfe/actor/Animation.h"
Animation::Animation()
{
  setCurrentFrame(0);
};
Animation::Animation(string imageSource,string frames,float OffsetX, float OffsetY, float fps, bool doesLoop,int finalFrame)
{
  setCurrentFrame(0);
  setModelSource(imageSource);
  setLoop(doesLoop);
  setOffset(OffsetX,0,OffsetY);
  setFinalFrame(finalFrame);
  setRate(fps);
  //setRotation(0,0,0);
  do
    {
      string FrameSelection=nextSet(&frames,',');
      if (FrameSelection!="")
	{
	  int newFrame=atoi(FrameSelection.c_str());
	  frames_.push_back(newFrame);
	};
    }while (frames.find(',')!=string::npos);
};

int Animation::getFrame()
{
  int Frame;
  int currentFrame=getCurrentFrame();
  if (getCurrentFrame()>frames_.size() && !getLoop())
    {
      return getFinalFrame();
    }
  else if (currentFrame>=frames_.size())
    {
      currentFrame=0;
    };
  if (frames_.size()==0)
    {
      return 0;
    };
  Frame=frames_.at((int)currentFrame);
  return Frame;
};
bool Animation::currentFramePlus()
{
  //TODO: Current Frame Lock
  currentFrame_+=getRate()*TBFE_Base::GameSpeed;
  //End Lock
  int currentFrame=getCurrentFrame();
  if (currentFrame>=frames_.size())
    {
      if (!getLoop())
	{
	  if (getFinalFrame()==-1)
	    {
	      return false;
	    }
	}
      else
	{
	  currentFrame_=0;
	};
    };
  return true;
};
ModelData * Animation::getModel()
{
  loadModel();
  return model_.Data;
};
void Animation::setModelSource(string newSource)
{
  model_.Source=newSource;
  model_.Data=NULL;
  model_.isLoaded=false;
};
bool Animation::loadModel()
{
  if (!model_.isLoaded)
    {
      model_.Data=TBFE_Base::CheckModels(model_.Source);
      model_.isLoaded=true;
    };
  return true;
};
PositionF Animation::getOffset()
{
  return offset_;
};
void Animation::reset()
{
  setCurrentFrame(0);
};
float Animation::getCurrentFrame()
{
  return currentFrame_;
};
void Animation::setCurrentFrame(float newFrame)
{
  currentFrame_=newFrame;
};
bool Animation::getLoop()
{
  return loop_;
};
void Animation::setLoop(bool newLoop)
{
  loop_=newLoop;
};
int Animation::getFinalFrame()
{
  return finalFrame_;
};
void Animation::setFinalFrame(int newFinalFrame)
{
  finalFrame_=newFinalFrame;
};
void Animation::setOffset(float x,float y, float z)
{
  offset_.X=x;
  offset_.Y=y;
  offset_.Z=z;
};
float Animation::getRate()
{
  return rate_;
};
void Animation::setRate(float newRate)
{
  rate_=newRate;
};
Quaternion Animation::getRotation()
{
  return rotation_;
};
void Animation::setRotation(Quaternion rotations)
{
  rotation_=rotations;
};
void Animation::rotate(Quaternion newRotation)
{
  rotation_*=newRotation;
};
