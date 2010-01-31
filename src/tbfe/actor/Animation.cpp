#include "Animation.h"
Animation::Animation()
{
  setCurrentFrame(0);
};
Animation::Animation(string imageSource,string frames,int width, int height,
		     int OffsetX, int OffsetY, float fps, bool doesLoop,int startX,int finalFrame)
{
  setCurrentFrame(0);
  setSheetSource(imageSource);
  setDimensions(width,height);
  setLoop(doesLoop);
  setStartX(startX);
  setOffset(OffsetX,OffsetY);
  setFinalFrame(finalFrame);
  setRate(fps);
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
  else if (currentFrame>frames_.size())
    {
      currentFrame=0;
    };
  Frame=frames_.at((int)currentFrame);
  return Frame;
};
SDL_Rect Animation::getFrameRect(Direction currentDirection)
{
  SDL_Rect FrameRect;
  Position DirectionOffset;
  Position ActionDimensions;
  Position Dimensions=getDimensions();
  int frame;
  int AnimationOffsetX;
  
  DirectionOffset.X=(currentDirection-(int)(currentDirection/2)*2);
  DirectionOffset.Y=(int)((int)currentDirection/2);
  frame=getFrame();
  
  DirectionOffset.X*=Dimensions.X;
  DirectionOffset.Y*=Dimensions.Y;
  
  ActionDimensions.X=Dimensions.X;
  ActionDimensions.Y=Dimensions.Y;
  AnimationOffsetX=2*ActionDimensions.X*frame;
  FrameRect.x=AnimationOffsetX+DirectionOffset.X;
  FrameRect.y=DirectionOffset.Y;
  FrameRect.w=ActionDimensions.X;
  FrameRect.h=ActionDimensions.Y;
  return FrameRect;
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
	  currentFrame=0;
	};
    };
  return true;
};
SDL_Surface * Animation::getSheet()
{
  loadSheet();
  return image_.Data;
};
void Animation::setSheetSource(string newSource)
{
  image_.Source=newSource;
  image_.Data=NULL;
  image_.isLoaded=false;
};
bool Animation::loadSheet()
{
  if (!image_.isLoaded)
    {
      image_.Data=TBFE_Base::CheckSheets(image_.Source);
      image_.isLoaded=true;
    };
  return true;
};
Position Animation::getOffset()
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
Position Animation::getDimensions()
{
  return dimensions_;
};
void Animation::setDimensions(int width,int height)
{
  dimensions_.X=width;
  dimensions_.Y=height;
};
bool Animation::getLoop()
{
  return loop_;
};
void Animation::setLoop(bool newLoop)
{
  loop_=newLoop;
};
int Animation::getStartX()
{
  return startX_;
};
void Animation::setStartX(int newStartX)
{
  startX_=newStartX;
};
int Animation::getFinalFrame()
{
  return finalFrame_;
};
void Animation::setFinalFrame(int newFinalFrame)
{
  finalFrame_=newFinalFrame;
};
void Animation::setOffset(int x, int y)
{
  offset_.X=x;
  offset_.Y=y;
};
float Animation::getRate()
{
  return rate_;
};
void Animation::setRate(float newRate)
{
  rate_=newRate;
};
