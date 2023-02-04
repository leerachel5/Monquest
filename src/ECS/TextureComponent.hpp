#ifndef TextureComponent_hpp
#define TextureComponent_hpp

#include "../AssetManager.hpp"
#include "ProjectorComponent.hpp"


class TextureComponent : public Component {
public:
    TextureComponent() {}
    TextureComponent(std::string id) {
        setTex(id);
    }
    ~TextureComponent() {}
    
    void setTex(std::string id) {
        texture = Game::assets->GetTexture(id);
    }
    
    void draw() override {
        ProjectorComponent projector = entity->getComponent<ProjectorComponent>();
        
        TextureManager::Draw(texture, &projector.srcRect, &projector.destRect);
    }
    
private:
    SDL_Texture* texture;
};

#endif /* TextureComponent_hpp */
