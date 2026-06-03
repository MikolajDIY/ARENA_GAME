#include "messages.h"
//-----------------------------------
//      MESSAGE MENAGER
//-----------------------------------

MessageMenager::MessageMenager(TextureMenager& tex) : textures(tex){}

// DODAWANIE KOMUNIKATOW DO WYSWIETLANIA
void MessageMenager::add(std::string name, MessageType mtype, float tim, sf::Color color, sf::Vector2f pos, float siz){
    Utils::GameMessage msg;
    msg.type = mtype;
    msg.info = name;
    msg.timeOfLife = tim;
    msg.clock.restart();
    msg.textColor = color;
    msg.position = pos;
    msg.size = siz;

    messagess.push_back(msg);
}
// USUWANIE PRZEDAWNIONYCH KOMUNIKATOW
void MessageMenager::update(){
    messagess.erase(std::remove_if(messagess.begin(),messagess.end(),[](Utils::GameMessage msg){
                                    return msg.clock.getElapsedTime().asSeconds() >= msg.timeOfLife;
                                   }), messagess.end());
}
// RYSOWANIE
void MessageMenager::Draw(sf::RenderWindow& window){
    int number = 0;
    int numberSpecial =0;
    float lastSize = 0;
    float lastSizeSpecial =0;
    for(auto& msg : messagess){
        sf::Text text(msg.info, textures.getMainFont(), msg.size);
        if(msg.type == MessageType::GameIfno){
                text.setFont(textures.getGameFont());
                text.setCharacterSize(msg.size);
        }

        if(number == 0){lastSize = msg.size;}
        if(numberSpecial == 0){lastSizeSpecial = msg.size;}

        Utils::CenterTextOrigin(text);

        switch(msg.type){
        case MessageType::Error:
            text.setFillColor(sf::Color::Red);
            break;

        case MessageType::Warning:
            text.setFillColor(sf::Color::Yellow);
            break;

        case MessageType::Success:
            text.setFillColor(sf::Color::Green);
            break;
        }

        if(msg.type == MessageType::GameIfno){
            text.setFillColor(msg.textColor);
            text.setPosition(msg.position + sf::Vector2f(0.0f, 1.1f * numberSpecial * lastSizeSpecial));
            lastSizeSpecial = msg.size;
            numberSpecial ++;
        }
        else{
            text.setPosition(400 ,500 + (number * lastSize));
            lastSize = msg.size;
        }

        window.draw(text);
        number ++;
    }
}

