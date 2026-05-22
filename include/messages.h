#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "utils.h"
#include "textureMenager.h"

enum class MessageType{Error, Warning, Success};

class MessageMenager{
private:
    TextureMenager& textures;
    std::vector<Utils::GameMessage> messagess;
public:
    MessageMenager(TextureMenager& tex);

    void add(std::string text, MessageType mtype, float tim);
    void update();
    void Draw(sf::RenderWindow& window);
};
