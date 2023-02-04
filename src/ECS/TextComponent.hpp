#ifndef TextComponent_hpp
#define TextComponent_hpp

#include "ECS.hpp"
#include <vector>

class TextComponent : public Component {
public:
    TextComponent() {}
    TextComponent(std::string _text) {
        text.push_back(_text);
    }
    TextComponent(std::vector<std::string> _text) {
        for (std::string t : _text) {
            text.push_back(t);
        }
    }
    ~TextComponent() {}
    
    void addText(std::string _text) {
        text.push_back(_text);
    }
    
    std::string getText() {
        return text.front();
    }
    
    void removeCurrentText() {
        text.erase(text.begin());
    }
    
    bool isEmpty() {
        return text.empty();
    }
    
    unsigned long numberOfTexts() {
        return text.size();
    }
    
private:
    std::vector<std::string> text;
};

#endif /* TextComponent_hpp */
