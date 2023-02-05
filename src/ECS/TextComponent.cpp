#include "TextComponent.hpp"


TextComponent::TextComponent() {}

TextComponent::TextComponent(std::string _text) {
    text.push_back(_text);
}

TextComponent::TextComponent(std::vector<std::string> _text) {
    for (std::string t : _text) {
        text.push_back(t);
    }
}

TextComponent::~TextComponent() {}

std::string TextComponent::getText() {
    return text.front();
}

bool TextComponent::TextComponent::isEmpty() {
    return text.empty();
}

unsigned long TextComponent::numberOfTexts() {
    return text.size();
}


void TextComponent::addText(std::string _text) {
    text.push_back(_text);
}

void TextComponent::removeCurrentText() {
    text.erase(text.begin());
}
