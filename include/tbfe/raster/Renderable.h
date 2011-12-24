#ifndef Renderable_L
#define Renderable_L
class Renderable
{
 private:
 public:
  RenderParameters * getParams()=0;
  void draw()=0;
};
#endif
