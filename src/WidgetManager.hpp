#ifndef WidgetManager_hpp
#define WidgetManager_hpp

#include <string>

class SDL_Color;
class Manager;
class Entity;


class WidgetManager {
public:
    static Entity* CreateWidget(Manager* manager, float x, float y, int w, int h, int sc);
    static Entity* CreateImageBox(Manager* manager, float x, float y, int w, int h, int sc, std::string texID);
    static Entity* CreateTextBox(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::string text, std::string fontID, int textSize, SDL_Color textColor);
    static Entity* CreateButton(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::string text, std::string fontID, int textSize, SDL_Color textColor, void (*f)());
    static Entity* CreateDialogueBox(Manager* manager, int xoffset, int yoffset, float x, float y, int srcw, int srch, int sc, std::string texID, std::vector<std::string> text, std::string fontID, int textSize, SDL_Color textColor);
};


#endif /* WidgetManager_hpp */
