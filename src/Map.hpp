#ifndef Map_hpp
#define Map_hpp

#include <string>

class Map {
public:
    Map(std::string tID, int mScale, int tSize);
    ~Map();
    
    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
    std::string textureID;
    int mapScale;
    int tileSize;
    int scaledSize;
};

#endif /* Map_hpp */
