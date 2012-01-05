#ifndef DirectoryFactory_L
#define DirectoryFactory_L
#include<string>
#include<map>
#include<iterator>
template<class T>
class DirectoryFactory
{
private:
  std::map<std::string,T> Ts;
  typedef std::map<std::string,T> mMap;
  typedef std::pair<std::string,T> mPair;
  typedef typename mMap::iterator mIt;
  T (* FactoryConstructor)(std::string);
  void (* FactoryDestructor)(T * );
 public:
 DirectoryFactory(T (*constructor)(std::string), void (*destructor)(T *) ) : 
  FactoryConstructor(constructor), FactoryDestructor(destructor) { }
  ~DirectoryFactory()
    {
      mIt it;
      
      for ( it=Ts.begin() ; it != Ts.end(); it++ )
	{
	  FactoryDestructor(&it->second);
	}
    }
  T FromFileName(std::string fileName)
  {
    mIt it=Ts.find(fileName);
    T t=it->second;
    if (it==Ts.end())
      {
	t=FactoryConstructor(fileName);
	if (!t.isNull())
	  {
	    mPair pair(*Ts.insert(Ts.begin(),mPair(fileName,t)));
	    t=pair.second;
	  }
      }
    return t;
  }
};
#endif
