#ifndef FontManager_hpp
#define FontManager_hpp

#include <SDL2_ttf/SDL_ttf.h>
#include <string>


class FontManager {
public:
    static TTF_Font *LoadFont(const char *path, int fontSize);
    static SDL_Texture *SetText(TTF_Font* font, int fontSize, std::string text, SDL_Color textColor);
    static void Draw(SDL_Texture* texture, int x, int y, SDL_Rect& src, SDL_Rect& dest);
};

#endif /* FontManager_hpp */
