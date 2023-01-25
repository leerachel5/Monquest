#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS/Components.hpp"

extern Manager manager;

Map::Map(std::string tID, int mScale, int tSize)
    : textureID{tID}, mapScale{mScale}, tileSize{tSize}, scaledSize{tSize * mScale}
{}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char c;
    std::fstream mapFile;
    mapFile.open(path);
    
    int srcX, srcY;
    
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }
    
    mapFile.ignore(); // Ignore blank line between terrain map and collider map
    
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            if (c == '1') {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(textureID, srcX, srcY, xpos, ypos, tileSize, mapScale);
    tile.addGroup(Game::groupMap);
}
