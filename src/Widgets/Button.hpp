#ifndef Button_hpp
#define Button_hpp

#include <SDL2/SDL.h>
#include "../ECS/ECS.hpp"


class Button {
public:
    Button(Manager* mngr);
    ~Button();
    
    void createButton(int x, int y, int w, int h, int sc, std::string text, std::string font, SDL_Color& color);
    Entity& getButton();
    
    void addFunction(void (*f) ());
    void executeFunction();

private:
    Manager* manager;
    Entity* button;
};

#endif /* Button_hpp */
