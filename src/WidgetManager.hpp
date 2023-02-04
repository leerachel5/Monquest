#ifndef WidgetManager_hpp
#define WidgetManager_hpp

#include "ECS/ECS.hpp"
#include <SDL2/SDL.h>


class WidgetManager {
public:
    static Entity* CreateWidget(Manager* manager, float x, float y, int w, int h, int sc);
    static Entity* CreateTextBox(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::string text, std::string fontID, int textSize, SDL_Color textColor);
    static Entity* CreateButton(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::string text, std::string fontID, int textSize, SDL_Color textColor, void (*f)());
};


#endif /* WidgetManager_hpp */
