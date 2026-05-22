#pragma once
#include <SFML/Graphics.hpp>
#include "theme.h"

class TextureMenager;
class MessageMenager;
enum class MessageType;
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

    inline void CenterSpriteOrigin(sf::Sprite& sprite){
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    }

    inline void CenterRectangleOrigin(sf::RectangleShape& shape){
        sf::FloatRect bounds = shape.getLocalBounds();
        shape.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    }

    struct Mouse{
        sf::Vector2f pos;
        bool clickedLeft = false;
        bool clickedRight = false;
    };

    struct GameMessage{
        MessageType type;
        std::string info;
        float timeOfLife;
        sf::Clock clock;
    };

    struct Menagers{
        TextureMenager& tex;
        MessageMenager& msg;

        Menagers(TextureMenager& t, MessageMenager& m) : tex(t), msg(m) {}
    };
}
