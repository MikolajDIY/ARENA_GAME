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
    const float TimeOfMessage = 2.f;

    template <typename T>
    class ObjectFormatter {
    public:
        // CENTROWANIE
        static void centerOrigin(T& object) {
            sf::FloatRect bounds = object.getLocalBounds();
            object.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
        }

        // FORMAT TEKSTU I JEGO CENTROWANIE
        static void formatText(sf::Text& text) {
            centerOrigin(text);
            // PONIEWAZ DOMYSLNIE UZYWAMY ZLOTEJ CZCIONKI TAKA USTAWIMY
            text.setOutlineColor(sf::Color::Black);
            text.setFillColor(Theme::Text);
            text.setOutlineThickness(3.f);
        }
    };

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
        sf::Color textColor;
        sf::Vector2f position;
        float size;
    };

    struct Menagers{
        TextureMenager& tex;
        MessageMenager& msg;

        Menagers(TextureMenager& t, MessageMenager& m) : tex(t), msg(m) {}
    };
}
