#include "Inventory.h"
Inventory::Inventory(int Size)
{
  setStackable(false);
  items_.resize(Size);
  amount_.resize(Size);
  for(int i=0;i<Size;i++)
    {
      items_.at(i)=-1;
      amount_.at(i)=0;
    };
};
void Inventory::set(int slot,int item,int Amount)
{
  //items Lock applies to both the item and amount vectors
  //TODO: items Lock
  if (slot>=items_.size())
  {
    TBFE_Base::MainConsole.write("Slot Number exceeds Inventory Size");
    return;
  };
  items_.at(slot)=item;
  amount_.at(slot)+=Amount;
};
int Inventory::get(int slot)
{
  //TODO: items Lock
  if (slot>=items_.size())
    {
      TBFE_Base::MainConsole.write("Slot Number exceeds Inventory Size");
      return 0;
    };
  return items_.at(slot);
};
int Inventory::getAmount(int slot)
{
  //TODO: items Lock
  if (slot>=amount_.size())
    {
      TBFE_Base::MainConsole.write("Slot Number exceeds Inventory Size");
      return 0;
    };
  return amount_.at(slot);
};
int Inventory::remove(int Slot,int Amount)
{
  //TODO: items Lock
  if (Slot>=items_.size())
    {
      TBFE_Base::MainConsole.write("Slot Number exceeds Inventory Size");
      return 0;
    };
  int type=items_.at(Slot);
  amount_.at(Slot)-=Amount;
  if (amount_.at(Slot)<0)
    {
      items_.at(Slot)=-1;
      amount_.at(Slot)=0;
    };
  return type;
};
bool Inventory::add(int Item,int Slot,int Amount)
{
  //TODO: Items Lock
  if (Slot>=items_.size())
    {
      TBFE_Base::MainConsole.write("Slot Number exceeds Inventory Size");
      return false;
    };
  if (Slot==0)
    {
      for (int i=0;i<items_.size();i++)
	{
	  if (items_.at(i)==-1 || (items_.at(i)==Item && getStackable()))
	    {
	      items_.at(i)=Item;
	      amount_.at(i)+=Amount;
	      return true;
	    };
	};
    }
  else
    {
      items_.at(Slot)=Item; 
      amount_.at(Slot)+=Amount;
    };
  return false;
};
bool Inventory::getStackable()
{
  return isStackable_;
};
void Inventory::setStackable(bool newStackable)
{
  isStackable_=newStackable;
};
