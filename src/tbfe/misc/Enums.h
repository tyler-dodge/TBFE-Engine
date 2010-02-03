#ifndef Enums_L
#define Enums_L
//only applies to Farm tiles
enum TileType
  {
    NONE,
    GRASS,
    DIRT,
    DIRT_TILLED,
    DIRT_TILLED_WATERED
  };
enum Direction
  {
    DOWN,
    UP,
    LEFT,
    RIGHT,
    QUIT,
    NORMAL,
    SECOND
  };
enum AI
  {
    STANDING,
    AIMLESS,
    TALKING
  };
enum Event
  {
    CLICK,
    MOUSEMOVE,
    KEYPRESS
  };
#endif
