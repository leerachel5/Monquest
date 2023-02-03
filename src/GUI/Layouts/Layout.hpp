#ifndef Layout_hpp
#define Layout_hpp


template <typename T>
class Layout {
public:
    Layout() {}
    Layout(int xpos, int ypos, int width, int height) : x{xpos}, y{ypos}, w{width}, h{height} {}
    virtual ~Layout() {}
    
    // Main loop functions
    virtual void init() = 0;
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    void setXToPercentOfWindow(int percent) {
        x = Game::windowW * percent / 100;
    }
    
    void setYToPercentOfWindow(int percent) {
        y = Game::windowH * percent / 100;
    }
    
    void setWidthToPercentOfWindow(int percent) {
        w = Game::windowW * percent / 100;
    }
    
    void setHeightToPercentOfWindow(int percent) {
        h = Game::windowH * percent / 100;
    }

public:
    int x, y, w, h;
};

#endif /* Layout_hpp */
