#include "TextureComponent.hpp"
#include "../Game.hpp"
#include "AssetManager.hpp"
#include "TextureManager.hpp"
#include "ProjectorComponent.hpp"


TextureComponent::TextureComponent() {}
TextureComponent::TextureComponent(std::string id) {
    setTex(id);
}
TextureComponent::~TextureComponent() {}

void TextureComponent::draw() {
    ProjectorComponent projector = entity->getComponent<ProjectorComponent>();
    TextureManager::Draw(texture, &projector.srcRect, &projector.destRect);
}


void TextureComponent::setTex(std::string id) {
    texture = Game::assets->GetTexture(id);
}
