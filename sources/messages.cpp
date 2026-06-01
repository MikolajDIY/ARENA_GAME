#include "messages.h"
//-----------------------------------
//      MESSAGE MENAGER
//-----------------------------------

MessageMenager::MessageMenager(TextureMenager& tex) : textures(tex){}

// DODAWANIE KOMUNIKATOW DO WYSWIETLANIA
void MessageMenager::add(std::string name, MessageType mtype, float tim){
    Utils::GameMessage msg;
    msg.type = mtype;
    msg.info = name;
    msg.timeOfLife = tim;
    msg.clock.restart();

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
    for(auto& msg : messagess){
        sf::Text text(msg.info, textures.getMainFont(), 15);
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

        text.setPosition(400 ,500 + (number*15));

        window.draw(text);
        number ++;
    }
}

