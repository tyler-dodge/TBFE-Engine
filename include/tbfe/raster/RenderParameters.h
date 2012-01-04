#ifndef RenderParameters_L
#define RenderParameters_L
class RenderParameters
{
 private:
 public:
  virtual void setUp()=0;
  virtual int hashCode();
  virtual void setUpInstance()=0;
  virtual void tearDownInstance()=0;
  virtual void tearDown()=0;
};
#endif
