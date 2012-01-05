#ifndef UniqueId_L
#define UniqueId_L
#define FIRST_ID 0
class Identifier
{
 private:
  static int nextId;
  int thisId;
 public:
  Identifier();
  int getId();
  bool operator<(Identifier *);
};
#endif
