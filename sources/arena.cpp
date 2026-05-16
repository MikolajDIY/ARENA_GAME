#include "arena.h"
#include "textureMenager.h"
#include "player.h"
#include "theme.h"

Arena::Arena(std::string arenaName, TextureMenager& textures, Player& mainPlayer) : textures(textures), player(mainPlayer){
    name = arenaName;
    currentState = TurnState::PlayerMove;
    btnBackToMenu = new Button("MENU", {10,10}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnBackToMenu->ChangeSize(90,40);


    // Wczytanie tekstur tla i przeciwnikow (tu lub w ich konstruktorach
                                             //Do przemyslenia)

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
    // Rysowanie Przeciwnikow
    // Rysowania Gracza
    player.Update();
    player.Draw(window);

    //Rysowanie Przyciskow
    btnBackToMenu->Draw(window);
}



