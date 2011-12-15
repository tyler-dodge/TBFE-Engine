#ifndef DirectoryFactory_L
#define DirectoryFactory_L
#include<D
class DirectoryFactory<T>
{
 public:
  virtual T FromFileName(string fileName)=0;
};
#endif
