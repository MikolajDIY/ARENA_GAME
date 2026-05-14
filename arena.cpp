#include "arena.h"
#include "textureMenager.h"
#include "player.h"

Arena::Arena(std::string arenaName, TextureMenager& textures, Player& mainPlayer) : textures(textures), player(mainPlayer){
    name = arenaName;
    currentState = TurnState::PlayerMove;
    btnBackToMenu = new Button("MENU", {10,10}, textures.getMainFont(), sf::Color::Red, sf::Color::Magenta);
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

    player.Draw(window);

    btnBackToMenu->Draw(window);
}



