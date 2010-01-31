#include "Action.h"
Action::Action(string name,string endScript)
{
  setName(name);
  setScript(endScript);
  animation_.resize(0);
  setDirection(DOWN);
};
Action::Action()
{
  setName("None");
  setScript("");
  animation_.resize(0);
  setDirection(DOWN);
};
void Action::addAnimation(Animation newAnimation,int Layer)
{
  if (Layer==-1)
    {
      animation_.push_back(newAnimation);
      return;
    };
  animation_.insert(animation_.begin()+Layer,newAnimation);
};
string Action::getName()
{
  return name_;
};
void Action::setName(string newName)
{
  name_=newName;
};
string Action::getScript()
{
  return endScript_;
};
void Action::setScript(string endScript)
{
  endScript_=endScript;
};
int Action::getMainAnimationNum()
{
  return mainAnimation_;
};
bool Action::setMainAnimation(int number)
{
  if (number<0 || number>animation_.size())
    {
      return false;
    };
  mainAnimation_=number;
  return true;
};
bool Action::setDirection(Direction direction)
{
  currentDirection_=direction;
  return true;
};
Animation * Action::getLayer(int layer)
{
  if (layer<0 || layer>animation_.size())
    {
      return NULL;
    };
  return &animation_.at(layer);
};
bool Action::animationPlus()
{
  for (int i=0;i<animation_.size();i++)
    {
      bool test=animation_.at(i).currentFramePlus();
      if (mainAnimation_==i && !test)
	{
	  return false;
	};
    };
  return true;
};
SDL_Rect Action::getFrameRect(int Layer)
{
  if (Layer<0 || Layer>animation_.size())
    {
      SDL_Rect newRect;
      newRect.x=0;
      newRect.y=0;
      newRect.w=0;
      newRect.h=0;
    };
  return animation_.at(Layer).getFrameRect(getDirection());
};
void Action::loadAnimation()
{
  for (int i=0;i<animation_.size();i++)
    {
      animation_.at(i).loadSheet();
    };
};
int Action::getLayerSize()
{
  return animation_.size();
};

void Action::reset()
{
  for (int i=0;i<animation_.size();i++)
    {
      animation_.at(i).reset();
    };
};
Direction Action::getDirection()
{
  return currentDirection_;
};
