#pragma once
#include <SFML/Graphics.hpp>

namespace Utils{
    inline void CenterTextOrigin(sf::Text& text){
        sf::FloatRect bounds = text.getLocalBounds();

        text.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    }
}
