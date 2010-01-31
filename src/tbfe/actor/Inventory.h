#include <vector>
#ifndef Inventory_L
#define Inventory_L
class Inventory
{
 private:
  vector<int> items_;
  vector<int> amount_;
  bool isStackable_;
 public:
  Inventory(int Size=3);
  int get(int);
  int getAmount(int);
  int remove(int Item=0,int Amount=1);
  void set(int,int,int Amount=0);
  bool add(int,int Slot=0,int Amount=0);
  bool getStackable();
  void setStackable(bool);
};
#endif
