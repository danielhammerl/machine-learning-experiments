//
// Created by Daniel Hammerl on 01.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_WORLDITEM_H
#define MACHINELEARNINGEXPERIMENTS_WORLDITEM_H

#include <string>
#include <SFML/Graphics.hpp>

class WorldItem {
public:
    WorldItem();

    ~WorldItem();

    void setPosition(sf::Vector2u pos);

    sf::Vector2u getPosition();

    sf::Color getColor();

protected:
    //void move(int x, int y);

private:
    sf::Vector2u position;
};


#endif //MACHINELEARNINGEXPERIMENTS_WORLDITEM_H
