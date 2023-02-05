#include "Map.hpp"
#include "ECS.hpp"
#include "GameStates/OverworldState.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/LinkComponent.hpp"
#include "ECS/TileComponent.hpp"
#include <fstream>
#include <sstream>
#include <unordered_map>


namespace {
    struct Link {
        std::string destMap;
        int destX, destY;
        
        Link(std::string dM, int dX, int dY) : destMap{dM}, destX{dX}, destY{dY} {}
    };
}

Map::Map() {}

Map::Map(std::string tID, std::string filePath, int szX, int szY, int mScale, int tSize)
    : textureID{tID}, path{filePath}, sizeX{szX}, sizeY{szY}, mapScale{mScale}, tileSize{tSize}, scaledSize{tSize * mScale}
{}

Map::~Map() {
}

void Map::LoadMap(Manager& manager) {
    manager.resetGroup(OverworldState::groupMap);
    manager.resetGroup(OverworldState::groupTallGrass);
    manager.resetGroup(OverworldState::groupColliders);
    manager.resetGroup(OverworldState::groupMapLinks);
    
    char c;
    std::fstream mapFile;
    mapFile.open(path);
    
    int srcX, srcY;
    
    
    // Parse terrain map
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;

            mapFile.get(c);
            srcX = atoi(&c) * tileSize;

            AddTile(manager, srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }
    
    mapFile.ignore();
    
    // Parse tall grass map
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            
            if (c == '1') {
                auto& tallGrass(manager.addEntity());
                tallGrass.addComponent<TileComponent>("tall grass", 0, 0, x * scaledSize, y * scaledSize, tileSize, mapScale);
                tallGrass.addGroup(OverworldState::groupTallGrass);
            }
            
            mapFile.ignore();
        }
    }

    mapFile.ignore();
    
    // Parse collider map
    for (int y = -1; y < sizeY + 1; y++) {
        for (int x = -1; x < sizeX + 1; x++) {
            mapFile.get(c);
            if (c == '1') {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(OverworldState::groupColliders);
            }
            mapFile.ignore();
        }
    }
    
    // Parse link specifiers
    mapFile.ignore();
    
    std::unordered_map<int, Link> linkSpecifiers;
    
    std::string line;
    while(std::getline(mapFile, line)) {
        if (line == "end")
            break;
        
        int mapID;
        std::string mapName;
        int destX, destY;
        
        std::stringstream ss(line);
        ss >> mapID >> mapName >> destX >> destY;
        
        Link l = Link(mapName, destX, destY);
        linkSpecifiers.insert({mapID, l});
    }
    
    // Parse link map
    for (int y = -2; y < sizeY + 2; y++) {
        for (int x = -2; x < sizeX + 2; x++) {
            mapFile.get(c);
            if (c != '0' && isdigit(c)) {
                Link linkedMap = linkSpecifiers.at(int(c) - '0');
                auto& link(manager.addEntity());
                link.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                link.addComponent<LinkComponent>(linkedMap.destMap, linkedMap.destX, linkedMap.destY);
                link.addGroup(OverworldState::groupMapLinks);
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(Manager& manager, int srcX, int srcY, int xpos, int ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(textureID, srcX, srcY, xpos, ypos, tileSize, mapScale);
    tile.addGroup(OverworldState::groupMap);
}
