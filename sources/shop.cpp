#include "shop.h"
#include "game.h"
#include "theme.h"
#include "utils.h"

Shop::Shop(TextureMenager& textures, Player& player, Utils::Mouse& mouse) : mouse(mouse), player(player), textures(textures){
    BackGround.setTexture(textures.getShopBackGround());
    shopState = ShopState::Armors;

    createButtons();
    createTexts();
    createItems();
 }

Shop::~Shop(){
    buttons.clear();
    texts.clear();
    items.clear();
 }

void Shop::createItems(){
    switch(shopState){
    case ShopState::Armors:
        items["SteelArmor"] = std::make_unique<Item>(textures.getPlayerTextureSteel(), textures.getMainFont(), sf::Vector2f(300,300), "Steel Armor", 100.0);
        items["GoodnessArmor"] = std::make_unique<Item>(textures.getPlayerTextureGodnes(), textures.getMainFont(), sf::Vector2f(500,300), "Goodness Armor", 1000.0);
        break;

    case ShopState::Swords:
        items["SteelSword"] = std::make_unique<Item>(textures.getSteelSwordTexture(), textures.getMainFont(), sf::Vector2f(300,200), "Steel Sword", 100.0);
        items["GoodnessSword"] = std::make_unique<Item>(textures.getGodnesSwordTexture(), textures.getMainFont(), sf::Vector2f(500,200), "Goodness Sword", 1000.0);
        break;

    }
}

void Shop::createTexts(){
    texts["Shop"] = sf::Text("Shop",textures.getMainFont(), 40);
    Utils::CenterTextOrigin(texts["Shop"]);
    texts["Shop"].setPosition(400,40);

    switch(shopState){
    case ShopState::Armors:

        break;

    case ShopState::Swords:

        break;
    }
}

void Shop::createButtons(){
    buttons["BackToMenu"] = std::make_unique<Button>("Menu", sf::Vector2f(10, 10), textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["BackToMenu"]->ChangeSize(80, 40);

    buttons["Armors"] = std::make_unique<Button>("Armors", textures.getMainFont(), sf::Vector2f(50, 200), sf::Vector2f(120, 50));
    buttons["Swords"] = std::make_unique<Button>("Swords", textures.getMainFont(), sf::Vector2f(50, 300), sf::Vector2f(120, 50));

    switch(shopState){
    case ShopState::Armors:

        break;

    case ShopState::Swords:

        break;

    }
}

void Shop::changeMenu(ShopState state){
    if(shopState == state){return;}
    shopState = state;
    buttons.clear();
    texts.clear();
    items.clear();

    createButtons();
    createTexts();
    createItems();
}

void Shop::itemsClicked(){
    std::string clicked = "";
    for(auto& item : items){
        if(item.second->IsClicked(mouse)){
            clicked = item.first;
        }
    }
    // Dokonywanie zakupu
}

void Shop::buttonsClicked(){
    std::string clicked ="";
    for(auto const& button : buttons){
        if(button.second->IsClicked(mouse)){
            clicked = button.first;
        }
    }
    if(clicked == ""){return;}
    if(clicked == "Armors"){
        changeMenu(ShopState::Armors);
    }
    else if(clicked == "Swords"){
        changeMenu(ShopState::Swords);
    }
}
// -------------------------------------
// RYSOWANIE SKLEPU
// -------------------------------------
bool Shop::Update(Utils::Mouse& m){
    if (buttons.find("BackToMenu") != buttons.end() && buttons["BackToMenu"]->IsClicked(m)) {
        return false;
    }
    mouse = m;

    // Czy gracz cos klika
    buttonsClicked();
    itemsClicked();
    return true;
 }

void Shop::Draw(sf::RenderWindow& window){
    window.draw(BackGround);
    // Itemy
    for(auto const& item : items){
        item.second->Draw(window);
    }
    // Przyciski
    for(auto const& button : buttons){
        button.second->Draw(window);
    }
    // Text
    for(auto const& text : texts){
        window.draw(text.second);
    }
 }
