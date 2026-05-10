#include "arena.h"

Arena::Arena(std::string arenaName, sf::Font font){
    name = arenaName;
    arenaFont = font;
    currentState = TurnState::PlayerMove;
    btnBackToMenu = new Button("MENU", {10,10}, arenaFont, sf::Color::Red, sf::Color::Magenta);
    btnBackToMenu->ChangeSize(70,40);
    btnBackToMenu->ChangePosition(10,10);
    // Wczytanie tekstur tla i przeciwnikow
}

Arena::~Arena(){
    delete btnBackToMenu;
}

void Arena::Fight(){
    // Mechanika walki
}

bool Arena::Update(int mouseX, int mouseY, bool isClicked) {
    if (btnBackToMenu->IsClicked(mouseX, mouseY, isClicked)) {
        return false;
    }

    Fight(); // Logika walki
    return true;
}

void Arena::Draw(sf::RenderWindow& window){
    // Rysowanie Areny
    btnBackToMenu->Draw(window);
}



