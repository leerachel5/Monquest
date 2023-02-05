#ifndef TextComponent_hpp
#define TextComponent_hpp

#include "ECS.hpp"
#include <vector>

class TextComponent : public Component {
public:
    TextComponent();
    TextComponent(std::string _text);
    TextComponent(std::vector<std::string> _text);
    ~TextComponent();
    
    // Accessor methods
    std::string getText();
    bool isEmpty();
    unsigned long numberOfTexts();
    
    // Mutator methods
    void addText(std::string _text);
    void removeCurrentText();
    
private:
    std::vector<std::string> text;
};

#endif /* TextComponent_hpp */
