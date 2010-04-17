#ifndef Enums_L
#define Enums_L
#define PI 3.14159265
#define DEG_RAD PI/180
#define RAD_DEG 180/PI
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
    MOUSEHOLD,
    MOUSEMOVE,
    KEYPRESS
  };
#endif
