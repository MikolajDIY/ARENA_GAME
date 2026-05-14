#include "shop.h"
#include "game.h"

 Shop::Shop(TextureMenager& textures, Player& player){
    btnBackToMenu = new Button("MENU", {10,10}, textures.getMainFont(), sf::Color::Red, sf::Color::Magenta);
    btnBackToMenu->ChangeSize(70,40);
    btnBackToMenu->ChangePosition(10,10);
 }

 Shop::~Shop(){
    delete btnBackToMenu;
 }

bool Shop::Update(int mouseX, int mouseY, bool isClicked){
    if (btnBackToMenu->IsClicked(mouseX, mouseY, isClicked)) {
        return false;
    }
    return true;
 }

void Shop::Draw(sf::RenderWindow& window){
    btnBackToMenu->Draw(window);
 }
