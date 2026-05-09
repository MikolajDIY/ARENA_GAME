#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

// Zadanie zostało wykonane w SFML 3.0.0 z powodu trudności z instalacją wersji 2.6.2 

int main() 
{
    const int screenWidth=800;
    const int screenHeight=600;
    sf::RenderWindow window(sf::VideoMode({screenWidth, screenHeight}), "DVD Bounce");
    window.setFramerateLimit(60); 
    sf::Texture dvdTexture;
    if(!dvdTexture.loadFromFile("logo.png"))
        std::cout << "Nie mozna wczytac obrazka" << std::endl;
    sf::Sprite dvdSprite(dvdTexture);
    dvdSprite.setScale({0.2f, 0.2f}); 
    sf::Vector2f velocity(3.0f, 3.0f);
    while(window.isOpen()) 
    {
        while(const std::optional event=window.pollEvent()) 
        {
            if(event->is<sf::Event::Closed>())
                window.close();
        }
        dvdSprite.move(velocity);
        sf::FloatRect bounds=dvdSprite.getGlobalBounds();
        if(bounds.position.x <= 0 || bounds.position.x + bounds.size.x >= screenWidth) 
        {
            velocity.x = -velocity.x; 
            dvdSprite.setColor(sf::Color(rand()%255, rand()%255, rand()%255));
        }
        if(bounds.position.y <= 0 || bounds.position.y + bounds.size.y >= screenHeight) 
        {
            velocity.y = -velocity.y; 
            dvdSprite.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }

        window.clear(sf::Color::Black);
        window.draw(dvdSprite);
        window.display();
    }
    return 0;
}