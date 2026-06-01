#include "game.h"
#include "arena.h"
#include "textureMenager.h"
#include "theme.h"
#include "utils.h"

//-------------------------------------------------------
//                  CLASS GAME
//-------------------------------------------------------


Game::Game()
    : msgs(textures),
     menagers(textures, msgs),
     player(textures),
     shop(menagers,player,mouse),
     settings(menagers, player, mouse)
    {
    window_width = 800;
    window_height = 600;
    menuBackGround.setTexture(textures.getMenuBackGround());
};

Game::~Game(){
    for(auto& button : buttons){
        delete button.second;
    }
}
// -------------------------------------
// PETLA GLOWNA GRY
// -------------------------------------
void Game::Run(){
    window.create(sf::VideoMode(window_width, window_height),"ARENA GAME");
    window.setFramerateLimit(60);
    // Dodanie ikony aplikacji
    sf::Image icon;
    icon.loadFromFile("img/icons/game.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    MenuState = GameState::Intro;

    buttons["btnStart"] = new Button("START", {275, 200}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnMenu"] = new Button("MENU", {275, 300}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnShop"] = new Button("SHOP", {275, 300}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnSettings"] = new Button("SETTINGS", {275, 400}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnExit"] = new Button("EXIT", {275, 500}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);

    while(window.isOpen()){
        sf::Event event;
        mouse.clickedLeft = false;
        mouse.clickedRight = false;

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){window.close();}
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){mouse.clickedLeft = true;}
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right){mouse.clickedRight = true;}

        }
        window.clear(sf::Color(30,30,30));

        mouse.pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));


        if (MenuState == GameState::Arena) {
            DisplayArena(window, mouse);
        }
        else if(MenuState == GameState::Shop){
            DisplayShop(window, mouse);
        }
        else if(MenuState == GameState::Settings){
            DisplaySettings(window, mouse);
        }
        else if(MenuState == GameState::MainMenu){
            DisplayMenu(window, mouse);
        }
        else if (MenuState == GameState::Intro) {
            DisplayIntro(window);
        }

        menagers.msg.update();
        menagers.msg.Draw(window);
        window.display();

    }
}
// -------------------------------------
// WYSWIETLANIE STANOW MENU
// -------------------------------------
// MENU
void Game::DisplayMenu(sf::RenderWindow& window, Utils::Mouse& Mouse){
    sf::Text title("The Arena", textures.getMainFont(), 60);
    Utils::CenterTextOrigin(title);
    title.setOutlineColor(sf::Color::Black);
    title.setFillColor(Theme::Text);
    title.setOutlineThickness(3.f);
    title.setPosition(400, 100);


    if(buttons["btnStart"]->IsClicked(Mouse)){
        MenuState = GameState::Arena;
    }
    if(buttons["btnShop"]->IsClicked(Mouse)){
        shop.OnEnter(); // Ekran startowy z pancerzami - podobnie mozna zrobic w settings
        MenuState = GameState::Shop;
    }
    if(buttons["btnSettings"]->IsClicked(Mouse)){
        MenuState = GameState::Settings;
    }
    if(buttons["btnExit"]->IsClicked(Mouse)){
        window.close();
    }

    window.draw(menuBackGround);
    for(auto const& button : buttons){
        button.second->Draw(window);
    }
    window.draw(title);

}
// ARENA
void Game::DisplayArena(sf::RenderWindow& window, Utils::Mouse& mouse){
    if (currentArena == nullptr) {
                currentArena = new Arena("Arena", menagers, player);
        }
        // Sprawdzamy, czy arena chce kontynuować działanie
        bool stayInArena = currentArena->Update(mouse);

        if (!stayInArena) {
            delete currentArena;
            currentArena = nullptr;
            MenuState = GameState::MainMenu;
        }
        else {
            currentArena->Draw(window);
        }
}
// USTAWIENIA
void Game::DisplaySettings(sf::RenderWindow& window, Utils::Mouse& mouse){
    if(!settings.Update(mouse)){
        MenuState = GameState::MainMenu;
    }
    else{
        settings.Draw(window);
    }
}
// SHOP
void Game::DisplayShop(sf::RenderWindow& window, Utils::Mouse& mouse){
    if(!shop.Update(mouse)){
        MenuState = GameState::MainMenu;
    }
    else{
        shop.Draw(window);
    }
}
// INTRO
void Game::DisplayIntro(sf::RenderWindow& window){
    // Czas wyświetlania jednego ekranu w sekundach
    const float displayTime = 1.0f;

    if(introStage >= 3){
        return;
    }

    // Inicjalizacja przy pierwszym wejściu do metody
    if (introStage == 0) {
            introSprite.setTexture(textures.getStudio()); // studio

        introClock.restart();
        introStage = 1;
    }

    // Zmiana na game name
    if (introClock.getElapsedTime().asSeconds() >= displayTime) {
        if (introStage == 1) {
            introStage = 2;
                introSprite.setTexture(textures.getGameName());

            introClock.restart();
        }
        else if (introStage == 2) {
            // Koniec intro, przełączamy stan gry na Menu Główne
            MenuState = GameState::MainMenu;
            introStage = 3;
        }
    }

    // Rysowanie aktualnego loga na ekranie
    window.draw(introSprite);
}

