#include "MainMenuState.hpp"
#include "Button.hpp"
#include "TransformComponent.hpp"
#include "UILabel.hpp"
#include "MouseController.hpp"


Button::Button(Manager* mngr) : manager{mngr} {}

Button::~Button() {}

void Button::createButton(int x, int y, int w, int h, int sc, std::string text, std::string font, SDL_Color& color) {
    button = &manager->addEntity();
    button->addComponent<TransformComponent>(x, y, w, h, sc);
    button->addComponent<SpriteComponent>("button");
    button->addComponent<UILabel>(x + w * sc / 12, y + h * sc / 5, text, font, sc * 6, color);
    button->addComponent<MouseController>();
    button->addGroup(MainMenuState::groupButtons);
}

Entity& Button::getButton() {
    return *button;
}
