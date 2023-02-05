#include "UILabelComponent.hpp"
#include "../Game.hpp"
#include "AssetManager.hpp"
#include "../FontManager.hpp"
#include "TextComponent.hpp"
#include "ProjectorComponent.hpp"


UILabelComponent::UILabelComponent() {}
UILabelComponent::UILabelComponent(int xoffset, int yoffset, std::string textFontID, int textFontSize, SDL_Color& tColor) {
    SetLabelPosition(xoffset, yoffset);
    SetLabelFont(textFontID, textFontSize, tColor);
}

UILabelComponent::~UILabelComponent() {
}

void UILabelComponent::init() {
    projector = &entity->getComponent<ProjectorComponent>();
    text = &entity->getComponent<TextComponent>();
}

void UILabelComponent::update() {
    textTexture = FontManager::SetText(font, fontSize, text->getText(), textColor);
    
    position.x = projector->destRect.x + xOffset;
    position.y = projector->destRect.y + yOffset;
}

void UILabelComponent::draw() {
    FontManager::Draw(textTexture, position.x, position.y);
}

void UILabelComponent::SetLabelFont(std::string fontID, int fontSz, SDL_Color tColor) {
    font = Game::assets->GetFont(fontID);
    fontSize = fontSz;
    textColor = tColor;
}

void UILabelComponent::SetLabelPosition(int xoffset, int yoffset) {
    xOffset = xoffset;
    yOffset = yoffset;
}
