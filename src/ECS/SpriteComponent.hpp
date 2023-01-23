#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Components.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;
    SpriteComponent(const char* texturePath);
    
    void setTex(const char* texturePath);
    
    void init() override;
    
    void update() override;
    
    void draw() override;

private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
};

#endif /* SpriteComponent_hpp */
