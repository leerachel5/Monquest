#include "TextBox.hpp"
#include "../../AssetManager.hpp"

TextBox::TextBox() {}

TextBox::TextBox(int xpos, int ypos, int w, int h, int sc) : Widget(xpos, ypos, w, h, sc) {}

TextBox::TextBox(int xpos, int ypos, int w, int h, int sc, std::string texID, std::string buttonText, std::string fontID, int fontSz, SDL_Color tColor)
: Widget(xpos, ypos, w, h, sc), text{buttonText}, fontSize{fontSz}, textColor{tColor} {
    backgroundTex = Game::assets->GetTexture(texID);
    font = Game::assets->GetFont(fontID);
}

TextBox::~TextBox() {}

void TextBox::init() {}

void TextBox::handleEvents(SDL_Event& event) {}

void TextBox::update() {
    textTexture = FontManager::SetText(font, fontSize, text, textColor);
}

void TextBox::draw() {
    if (backgroundTex != nullptr)
        TextureManager::Draw(backgroundTex, srcRect, destRect);
    FontManager::Draw(textTexture, destRect->x + destRect->w / 10, destRect->y + destRect->h / 5, *srcRect, *destRect);
}

void TextBox::setTexture(std::string texID) {
    backgroundTex = Game::assets->GetTexture(texID);
}

void TextBox::setFont(std::string fontID, int fontSz, SDL_Color tColor) {
    font = Game::assets->GetFont(fontID);
    fontSize = fontSz;
    textColor = tColor;
}

void TextBox::setText(std::string buttonText) {
    text = buttonText;
}
