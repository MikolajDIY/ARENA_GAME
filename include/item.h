#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "utils.h"

//---------------------------------------------
//      OBECNIE ITEM JEST TYKO DLA SKLEPU
//---------------------------------------------

enum class SwordsTypes{Basic, Steel, Godness};
enum class ArmorsTypes{Basic, Steel, Godness};

class Item{
private:
    sf::Sprite itemSprite;
    sf::RectangleShape background;
    sf::Text nameText;
    sf::Text priceText;
    bool isHovered = false;

    int price;

public:
    Item(sf::Texture& texture, sf::Font& font, sf::Vector2f pos, std::string name, int pricee);

    int getPrice();
    bool IsClicked(Utils::Mouse& mouse, bool isBought);
    void Draw(sf::RenderWindow& window);
};
