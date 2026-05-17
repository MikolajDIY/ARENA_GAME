#pragma once
#include <SFML/Graphics.hpp>
//--------------------------------------
// FUNKCJE KTORE BEDZIEMY CZESTO UZYWAC
//--------------------------------------
namespace Utils{
    inline void CenterTextOrigin(sf::Text& text){
        sf::FloatRect bounds = text.getLocalBounds();

        text.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
        // PONIEWAZ DOMYSLNIE UZYWAMY ZLOTEJ CZCIONKI TKA USTAWIMY
        text.setOutlineColor(sf::Color::Black);
        text.setFillColor(Theme::Text);
        text.setOutlineThickness(3.f);
    }
}
