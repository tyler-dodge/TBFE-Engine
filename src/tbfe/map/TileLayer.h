#ifndef TileLayer_L
#define TileLayer_L
class TileLayer
{
 private:
  vector<Tile> data_;
  Position dimensions_;
  bool isVisible_;
 public:
  TileLayer(int,int);
  TileLayer();
  void generateMap(int,int,Tile);
  Position getDimensions();
  Tile getTile(int,int);
  void changeTile(int,int,Tile);
  bool getVisibility();
  void setVisibility(bool);
};
#endif
