#ifndef DirectoryFactory_L
#define DirectoryFactory_L
#include<string>
template<class T>
class DirectoryFactory
{
 public:
  virtual T FromFileName(std::string fileName)=0;
};
#endif
