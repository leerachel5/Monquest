#ifndef TextureComponent_hpp
#define TextureComponent_hpp

#include "ECS.hpp"
#include <string>

class SDL_Texture;


class TextureComponent : public Component {
public:
    TextureComponent();
    TextureComponent(std::string id);
    ~TextureComponent();
    
    void draw() override;
    
    void setTex(std::string id);
    
private:
    SDL_Texture* texture;
};

#endif /* TextureComponent_hpp */
