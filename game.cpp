#include "game.h"
#include "arena.h"
#include "textureMenager.h"
//-------------------------------------------------------
//                  CLASS BUTTON
//-------------------------------------------------------


Button::Button(std::string text, sf::Vector2f pos, sf::Font& font, sf::Color normalC, sf::Color hoverC){
    normalColor = normalC;
    hoverColor = hoverC;
    Position = pos;

    shape.setSize(sf::Vector2f(250, 60));
    shape.setPosition(Position);
    shape.setFillColor(normalColor);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);

    buttonText.setPosition(
        Position.x + (shape.getSize().x / 2.f) - (buttonText.getGlobalBounds().width / 2.f), Position.y +10
    );
}

bool Button::IsClicked(int mouseX, int mouseY, bool MouseClicked){
    sf::Vector2f mousePos(static_cast<float>(mouseX), static_cast<float>(mouseY));
    bool Hoverd = shape.getGlobalBounds().contains(mousePos);

    if(Hoverd){
        shape.setFillColor(hoverColor);
    }
    else{
        shape.setFillColor(normalColor);
    }
    return Hoverd && MouseClicked;
}

void Button::Draw(sf::RenderWindow& window){
    window.draw(shape);
    window.draw(buttonText);
}

void Button::ChangePosition(float x, float y){
    Position.x = x;
    Position.y = y;
    shape.setPosition(Position);
    buttonText.setPosition(
        Position.x + (shape.getSize().x / 2.f) - (buttonText.getGlobalBounds().width / 2.f), Position.y +10
    );
}
void Button::ChangeSize(float x, float y){
    shape.setSize(sf::Vector2f(x,y));
    fontSize = y/2;
    buttonText.setCharacterSize(fontSize);
}


//-------------------------------------------------------
//                  CLASS GAME
//-------------------------------------------------------


Game::Game() : player(textures){
    window_width = 800;
    window_height = 600;
};

Game::~Game(){
    delete btnMenu;
    delete btnSettings;
    delete btnStart;
}

void Game::Run(){
    window.create(sf::VideoMode(window_width, window_height),"ARENA GAME");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("fonts/porkybold.otf")) {
        // Zapasowy plan, gdyby PorkyBold sie nie chcial wczytac
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    GameState MenuState = GameState::MainMenu;

    btnStart = new Button("START", {275,200}, textures.getMainFont(), sf::Color::Blue, sf::Color::Cyan);
    btnSettings = new Button("SETTINGS", {275, 300}, textures.getMainFont(), sf::Color::Blue, sf::Color::Cyan);
    btnMenu = new Button("MENU",{275,300},textures.getMainFont(),sf::Color::Blue, sf::Color::Cyan);

    while(window.isOpen()){
        sf::Event event;
        isMouseClicked_Left = false;
        isMouseClicked_Right = false;

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){window.close();}
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){isMouseClicked_Left = true;}
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right){isMouseClicked_Right = true;}

        }
        window.clear(sf::Color(30,30,30));

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);


        if (MenuState == GameState::Arena) {
            DisplayArena(window, textures ,MenuState,mousePos);
        }

        else if(MenuState == GameState::Settings){
            DisplaySettings(window, textures ,MenuState,mousePos);
        }
        else if(MenuState == GameState::MainMenu){
            DisplayMenu(window, textures, MenuState, mousePos);
        }
        window.display();

    }
}

void Game::DisplayMenu(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    sf::Text title("MENU", textures.getMainFont(), 60);
    title.setPosition(280, 100);
    window.draw(title);

    if(btnStart->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Arena;
    }
    if(btnSettings->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Settings;
    }

    btnStart->Draw(window);
    btnSettings->Draw(window);

}

void Game::DisplayArena(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    if (currentArena == nullptr) {
                currentArena = new Arena("Arena", textures, player);
            }

            // Sprawdzamy, czy arena chce kontynuować działanie
            bool stayInArena = currentArena->Update(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left);

            if (!stayInArena) {
                delete currentArena;
                currentArena = nullptr;
                Menu_State = GameState::MainMenu;
            }
            else {
                currentArena->Draw(window);
            }
}

void Game::DisplaySettings(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    sf::Text title("SETTINGS", textures.getMainFont(),60);
    title.setPosition(280,100);
    window.draw(title);

    if(btnMenu->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::MainMenu;
    }
    btnMenu->Draw(window);

}

