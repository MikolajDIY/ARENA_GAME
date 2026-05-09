#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

int x_size = 640;
int y_size = 480;
int r,g,b;
sf::Sprite sprite;

void colorChange(){
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
    sprite.setColor(sf::Color(r, g, b));
}

int main()
{
    srand(time(NULL));
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;

   sf::RenderWindow window(sf::VideoMode(x_size, y_size), "SFML Project!");
    sf::Clock clock;
     sf::Texture texture;
    if (!texture.loadFromFile("img/dvd.png"))
    {
        return -1; // b³¹d ³adowania
    }

    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    float speed = 7.345;
    float speed_y = speed;
    float speed_x = speed;
    float x = 0;
    float y = 0;

    sf::FloatRect bounds = sprite.getGlobalBounds();
   while (window.isOpen())
   {
       if (clock.getElapsedTime().asSeconds() > 0.056f)
    {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();
      }
      if(x + bounds.width> x_size){
        x = x_size - bounds.width;
        speed_x = - speed_x;
        colorChange();
      }
      else if(x< 0){
        x = 0;
        speed_x = -speed_x;
        colorChange();
      }

      if(y + bounds.height> y_size){
        y = y_size - bounds.height;
        speed_y = -speed_y;
        colorChange();
      }
      else if(y < 0){
        y = 0;
        speed_y = -speed_y;
        colorChange();
      }
      sprite.setPosition(x, y);
      x = x + speed_x;
      y = y + speed_y;

      window.clear();
      // rysowanie czegoœ
      window.draw(sprite);
      window.display();
      clock.restart();
    }
   }
   return 0;
}
