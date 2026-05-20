#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "utils.h"

class Button{
private:
    sf::RectangleShape shape;
    sf::Text buttonText;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Vector2f Position;
    int fontSize;

public:
    // Konstruktor domyslny
    Button(std::string text, sf::Vector2f pos, sf::Font& font, sf::Color normalC, sf::Color hoverC);
    // Uproszczony - domysle kolory i czcionka
    Button(std::string text, sf::Vector2f pos, sf::Vector2f siz);

    bool IsClicked(Utils::Mouse& mouse);

    void Draw(sf::RenderWindow& window);
    void ChangePosition(float x, float y);
    void ChangeSize(float x, float y);
    void ChangeTextColor(sf::Color color);
};
