#ifndef Map_hpp
#define Map_hpp

#include <string>

class Map {
public:
    Map();
    Map(std::string tID, std::string filePath, int szX, int szY, int mScale, int tSize);
    ~Map();
    
    void LoadMap();
    void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
    std::string textureID;
    std::string path;
    int sizeX, sizeY;
    int mapScale;
    int tileSize;
    int scaledSize;
};

#endif /* Map_hpp */
