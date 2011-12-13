#include "tbfe/actor/Action.h"
Action::Action(string name,string endScript)
{
  setName(name);
  setScript(endScript);
  animation_.resize(0);
};
Action::Action()
{
  setName("None");
  setScript("");
  animation_.resize(0);
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
void Action::loadAnimation()
{
  for (int i=0;i<animation_.size();i++)
    {
      animation_.at(i).loadModel();
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
