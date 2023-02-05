#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "ECS.hpp"
#include <SDL2/SDL.h>

#include "../Vector2D.hpp"


class TileComponent : public Component {
public:
    TileComponent();
    TileComponent(std::string id, int srcX, int srcY, int xpos, int ypos, int tsize, int tscale);
    ~TileComponent();
    
    void update() override;
    void draw() override;
    
public:
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
};

#endif /* TileComponent_hpp */
