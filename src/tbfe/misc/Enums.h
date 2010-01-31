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
enum PlantType
  {
    NO_PLANT
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
enum Tools
  {
    HOE,
    WATERING_CAN,
    SICKLE,
    HAMMER,
    AXE,
    SEEDS
  };
enum PStats
  {
    FATIGUE,
    ENERGY,
    HUNGER,
    THIRST,
    CLEANLINESS,
    MONEY
  };
enum HairColor
  {
    BROWN,
    GRAY,
    BLACK,
    BLONDE,
    RED
  };
enum BodyParts
  {
    BODY=-1,
    TORSO,
    HAIR,
    FACIAL_HAIR,
    LEGS,
    TOOL,
    HEAD
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
