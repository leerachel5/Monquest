#ifndef MapManager_hpp
#define MapManager_hpp

#include <string>
#include <unordered_map>
#include "Map.hpp"
#include "ECS/ECS.hpp"

class MapManager {
public:
    MapManager();
    ~MapManager();
    
    void init(Manager* manager, std::string mapName, std::string texID, std::string fPath, int szX, int szY, int mapSc, int tileSz);
    
    void addMap(std::string mapName, std::string texID, std::string fPath, int szX, int szY, int mapSc, int tileSz);
    void loadMap(Manager* manager, std::string mapName);
    
    Map& getMap(std::string mapID);

public:
    std::string activeMap;
    
private:
    std::unordered_map<std::string, Map> maps;
};

#endif /* MapManager_hpp */
