#include "WidgetManager.hpp"
#include "Components.hpp"


Entity* WidgetManager::CreateWidget(Manager* manager, float x, float y, int w, int h, int sc) {
    Entity* widget(&manager->addEntity());
    
    widget->addComponent<TransformComponent>(x, y, w, h, sc);
    widget->addComponent<ProjectorComponent>();
    
    return widget;
}

Entity* WidgetManager::CreateImageBox(Manager* manager, float x, float y, int w, int h, int sc, std::string texID) {
    Entity* widget = CreateWidget(manager, x, y, w, h, sc);
    widget->addComponent<TextureComponent>(texID);
    return widget;
}

Entity* WidgetManager::CreateTextBox(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::string text, std::string fontID, int textSize, SDL_Color textColor) {
    Entity* widget = CreateWidget(manager, x, y, srcw, srch, sc);
    
    widget->addComponent<TextureComponent>(texID);
    widget->addComponent<TextComponent>(text);
    widget->addComponent<UILabelComponent>(xoffset, yoffset, fontID, textSize, textColor);
    
    return widget;
}

Entity* WidgetManager::CreateButton(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::string text, std::string fontID, int textSize, SDL_Color textColor, void (*f)()) {
    Entity* widget = CreateWidget(manager, x, y, srcw, srch, sc);
    
    widget->addComponent<TextureComponent>(texID);
    widget->addComponent<TextComponent>(text);
    widget->addComponent<UILabelComponent>(xoffset, yoffset, fontID, textSize, textColor);
    widget->addComponent<ButtonComponent>(f);
    
    ProjectorComponent* projector = &widget->getComponent<ProjectorComponent>();
    projector->AddAnimation("default", 0, 1, 1);
    projector->AddAnimation("hover", 1, 1, 1);
    projector->PlayAnimation("default");
    projector->ToggleAnimation(true);
    
    return widget;
}

Entity* WidgetManager::CreateDialogueBox(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::vector<std::string> text, std::string fontID, int textSize, SDL_Color textColor) {
    Entity* widget = CreateButton(manager, xoffset, yoffset, x, y, srcw, srch, sc, texID, text.front(), fontID, textSize, textColor, [](){});
    
    text.erase(text.begin());
    
    TextComponent* textComponent = &widget->getComponent<TextComponent>();
    for (std::string t : text)
        textComponent->addText(t);
    
    return widget;
}
