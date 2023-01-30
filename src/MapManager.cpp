#include "MapManager.hpp"


MapManager::MapManager() : activeMap{""} {}

MapManager::~MapManager() {}

void MapManager::init(std::string mapName, std::string texID, std::string fPath,
                      int szX, int szY, int mapSc, int tileSz) {
    Map initialMap = Map(texID, fPath, szX, szY, mapSc, tileSz);
    maps.emplace(std::make_pair(mapName, initialMap));
    
    initialMap.LoadMap();
    activeMap = mapName;
}

void MapManager::addMap(std::string mapName, std::string texID, std::string fPath, int szX, int szY, int mapSc, int tileSz) {
    Map m = Map(texID, fPath, szX, szY, mapSc, tileSz);
    maps.emplace(std::make_pair(mapName, m));
}

void MapManager::loadMap(std::string mapName) {
    if (mapName != activeMap) {
        maps[mapName].LoadMap();
        activeMap = mapName;
    }
}
