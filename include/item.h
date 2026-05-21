#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "utils.h"

//---------------------------------------------
//      OBECNIE ITEM JEST TYKO DLA SKLEPU
//---------------------------------------------

class Item{
private:
    sf::Sprite itemSprite;
    sf::RectangleShape background;
    sf::Text nameText;
    sf::Text priceText;
    bool isHovered = false;
    bool isBought = false;

public:
    Item(sf::Texture& texture, sf::Font& font, sf::Vector2f pos, std::string name, float price);

    bool IsClicked(Utils::Mouse& mouse);
    void Draw(sf::RenderWindow& window);
};
