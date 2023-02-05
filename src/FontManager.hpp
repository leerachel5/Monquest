#ifndef FontManager_hpp
#define FontManager_hpp

#include <string>

class _TTF_Font;
class SDL_Color;
class SDL_Texture;


class FontManager {
public:
    static _TTF_Font *LoadFont(const char *path, int fontSize);
    static SDL_Texture *SetText(_TTF_Font* font, int fontSize, std::string text, SDL_Color textColor);
    static void Draw(SDL_Texture* texture, int x, int y);
};

#endif /* FontManager_hpp */
