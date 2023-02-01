#ifndef Map_hpp
#define Map_hpp

#include "ECS/ECS.hpp"
#include <string>

class Map {
public:
    Map();
    Map(std::string tID, std::string filePath, int szX, int szY, int mScale, int tSize);
    ~Map();
    
    void LoadMap(Manager& manager);
    void AddTile(Manager& manager, int srcX, int srcY, int xpos, int ypos);
    void AddTallGrass(Manager& manager, int srcX, int srcY, int xpos, int ypos);
    
public:
    int sizeX, sizeY;
    int mapScale;
    int tileSize;
    int scaledSize;
    
private:
    std::string textureID;
    std::string path;
};

#endif /* Map_hpp */
