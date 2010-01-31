#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>
using namespace std;
class bobDole
{
private:
public:
  int poop;
  void test();
};
void bobDole::test()
{
  cout << poop << "\n";
};
bobDole Dole;
boost::mutex blocker;
void thready();
void testFunky(int a)
{
  cout << "start\n";
  boost::posix_time::seconds workTime(3);
  boost::posix_time::seconds workTime2(1);
  for (int i=0;i<5;i++)
    {
      blocker.lock();
      Dole.poop++;
      boost::this_thread::sleep(workTime);
      blocker.unlock();
      boost::this_thread::sleep(workTime2);
    };
  cout << "end\n";
};
void thready()
{
  cout << "poop\n";
};
int main()
{
  Dole.poop=25;
  using namespace boost;
  boost::thread test1234(testFunky,5);
  boost::posix_time::seconds workTime(1);
  boost::posix_time::seconds workTime2(3);
  cout << "start2\n";
  for (int i=0;i<5;i++)
    {
      blocker.lock();
      cout << Dole.poop << "\n";;
      boost::this_thread::sleep(workTime);
      blocker.unlock();
      boost::this_thread::sleep(workTime2);
    };
  cout << "end2\n";
  test1234.join();
  cout << Dole.poop << "\n";
};
