#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "utils.h"

//---------------------------------------------
//      OBECNIE ITEM JEST TYKO DLA SKLEPU
//---------------------------------------------

enum class SwordsTypes{Basic, Steel, Godness};
enum class ArmorsTypes{Basic, Steel, Godness};

struct ItemStats{
    int value; // Dla miecza, demage dla zbroji HP. Jezeli bedziecie chcieli mozna
                // dodac punkty mocy lub cos tego typu
};

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
    bool IsClicked(Utils::Mouse& mouse); // Specjalne dla Shop - wyswietlenie komunikatu, ze juz posiada;
    void Draw(sf::RenderWindow& window);
};

// STATYSTYKI ITEMOW - BITEWNE
namespace Stats{
    inline const std::map<ArmorsTypes, ItemStats> armor{
        {ArmorsTypes::Basic,{10}},
        {ArmorsTypes::Steel,{30}},
        {ArmorsTypes::Godness,{100}}
    };

    inline const std::map<SwordsTypes, ItemStats> sword{
        {SwordsTypes::Basic,{100}},
        {SwordsTypes::Basic,{300}},
        {SwordsTypes::Basic,{1000}}
    };
}
