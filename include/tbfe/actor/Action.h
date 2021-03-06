class Action;
#ifndef Action_L
#define Action_L
#include "tbfe/actor/Animation.h"
class Action
{
 private:
  vector<Animation> animation_;
  int mainAnimation_;
  std::string name_;
  std::string endScript_;
  Direction currentDirection_;
 public:
  Action(string,string);
  Action();
  void addAnimation(Animation,int Layer=-1);
  string getName();
  void setName(string);
  string getScript();
  void setScript(string);
  int getMainAnimationNum();
  bool setMainAnimation(int);
  bool animationPlus();
  void loadAnimation();
  Animation * getLayer(int);
  int getLayerSize();
  void reset();
};
#endif
