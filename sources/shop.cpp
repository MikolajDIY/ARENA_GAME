#include "shop.h"
#include "game.h"
#include "theme.h"
#include "utils.h"

Shop::Shop(Utils::Menagers& menagers, Player& player, Utils::Mouse& mouse)
    : mouse(mouse),
     player(player),
     menagers(menagers){

    BackGround.setTexture(menagers.tex.getShopBackGround());
    shopState = ShopState::Armors;

    createButtons();
    createTexts();
    createItems();
 }

Shop::~Shop(){
    buttons.clear();
    texts.clear();
    armors.clear();
    swords.clear();
 }

void Shop::createItems(){
    switch(shopState){
    case ShopState::Armors:
        armors[ArmorsTypes::Steel] = std::make_unique<Item>(menagers.tex.getPlayerTextureSteel(), menagers.tex.getMainFont(), sf::Vector2f(300,300), "Steel Armor", 100);
        armors[ArmorsTypes::Godness] = std::make_unique<Item>(menagers.tex.getPlayerTextureGodnes(), menagers.tex.getMainFont(), sf::Vector2f(500,300), "Goodness Armor", 1000);
        break;

    case ShopState::Swords:
        swords[SwordsTypes::Steel] = std::make_unique<Item>(menagers.tex.getSteelSwordTexture(), menagers.tex.getMainFont(), sf::Vector2f(300,200), "Steel Sword", 100);
        swords[SwordsTypes::Godness] = std::make_unique<Item>(menagers.tex.getGodnesSwordTexture(), menagers.tex.getMainFont(), sf::Vector2f(500,200), "Goodness Sword", 1000);
        break;

    }
}

void Shop::createTexts(){
    texts["Shop"] = sf::Text("Shop", menagers.tex.getMainFont(), 40);
    Utils::CenterTextOrigin(texts["Shop"]);
    texts["Shop"].setPosition(400,40);

    texts["Gold"] = sf::Text("Gold: " + std::to_string(player.getGold()) + " G",menagers.tex.getMainFont(), 20);
    Utils::CenterTextOrigin(texts["Gold"]);
    texts["Gold"].setPosition(700,40);

    switch(shopState){
    case ShopState::Armors:
        // Text dla pancerzy


    case ShopState::Swords:
        // Text dla mieczy
        break;
    }
}

void Shop::createButtons(){
    buttons["BackToMenu"] = std::make_unique<Button>("Menu", sf::Vector2f(10, 10), menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["BackToMenu"]->ChangeSize(80, 40);

    buttons["Armors"] = std::make_unique<Button>("Armors", menagers.tex.getMainFont(), sf::Vector2f(50, 200), sf::Vector2f(120, 50));
    buttons["Swords"] = std::make_unique<Button>("Swords", menagers.tex.getMainFont(), sf::Vector2f(50, 300), sf::Vector2f(120, 50));

    switch(shopState){
    case ShopState::Armors:
        // Przyciski dla Pancerzy
        break;

    case ShopState::Swords:
        // Przyciski dla Mieczy
        break;

    }
}

void Shop::changeMenu(ShopState state){
    if(shopState == state){return;}
    shopState = state;
    buttons.clear();
    texts.clear();
    swords.clear();
    armors.clear();

    createButtons();
    createTexts();
    createItems();
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
// ZAKUPY ITEMOW
void Shop::itemsClicked(){
    switch(shopState){
    case ShopState::Armors:
        for(auto& armor : armors){
            if(armor.second->IsClicked(mouse) && player.hasArmor(armor.first)){
                 menagers.msg.add("You already bought this armor!", MessageType::Warning, Utils::TimeOfMessage);
            }
            if(armor.second->IsClicked(mouse, player.hasArmor(armor.first))){
                if(player.buyArmor(armor.first, armor.second->getPrice())){
                    texts["Gold"].setString("Gold: " + std::to_string(player.getGold())+ " G"); // Aktualizacaja stanu konta na ekranie;
                    menagers.msg.add("Take and win!", MessageType::Success, Utils::TimeOfMessage);
                    break;
                }
                else{
                    // wyswietlenie bledu za malo golda
                    menagers.msg.add("You have not enought gold to buy this armor!", MessageType::Error, Utils::TimeOfMessage);
                }
                // Trzeba dodac tutaj wyswietlanie tekstu "posiadane", lub "brak srodkow"
            }          // Do przemyslenia
        }
        break;

    case ShopState::Swords:
        for(auto& sword : swords){
            if(sword.second->IsClicked(mouse) && player.hasSword(sword.first)){
                menagers.msg.add("You already bought this sword!", MessageType::Warning, Utils::TimeOfMessage);
            }
            if(sword.second->IsClicked(mouse, player.hasSword(sword.first))){
                if(player.buySword(sword.first, sword.second->getPrice())){
                    texts["Gold"].setString("Gold: " + std::to_string(player.getGold())+ " G");
                    menagers.msg.add("Take and win!", MessageType::Success, Utils::TimeOfMessage);
                    break;
                }
                else{
                    // wyswietlenie bledu za malo golda
                    menagers.msg.add("You have not enought gold to buy this sword!", MessageType::Error, 2.f);
                }
            }
        }
        break;
    }
}

// -------------------------------------
// RYSOWANIE SKLEPU
// -------------------------------------
void Shop::OnEnter(){
    changeMenu(ShopState::Armors);
}

bool Shop::Update(Utils::Mouse& m){
    if (buttons.find("BackToMenu") != buttons.end() && buttons["BackToMenu"]->IsClicked(m)) {
        return false;
    }
    mouse = m;

    // Czy gracz cos klika - uruchomienie logiki sklepu i animacji
    buttonsClicked();
    itemsClicked();
    return true;
 }

void Shop::Draw(sf::RenderWindow& window){
    window.draw(BackGround);
    // Itemy
    for(auto const& sword : swords){
        sword.second->Draw(window);
    }
    for(auto const& armor : armors){
        armor.second->Draw(window);
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
