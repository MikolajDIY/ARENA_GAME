#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory> // Mo¿e z³apiemy wiêcej punktów (inteligentne wskaŸniki)
#include "textureMenager.h"
#include "item.h"
#include "utils.h"
class Button;
class Player;

enum class ShopState{Armors,Swords};
class Shop{
private:
    sf::Sprite BackGround;
    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::map<std::string, std::unique_ptr<Item>> items;
    std::map<std::string, sf::Text> texts;
    Utils::Mouse& mouse;
    TextureMenager& textures;
    ShopState shopState;

    Player& player;

public:
    Shop(TextureMenager& textures, Player& player, Utils::Mouse& mouse);
    ~Shop();
    // Zmiany stanow Menu Sklepu
    void createButtons();
    void createTexts();
    void createItems();
    void changeMenu(ShopState state);

    // Sprawdzenie czy przycisk klikniety
    void buttonsClicked();
    void itemsClicked();

    // Rysowanie sklepu
    bool Update(Utils::Mouse& mouse);
    void Draw(sf::RenderWindow& window);
};

