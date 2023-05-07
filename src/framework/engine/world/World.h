//
// Created by Daniel Hammerl on 01.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_WORLD_H
#define MACHINELEARNINGEXPERIMENTS_WORLD_H


#include "WorldItem.h"
#include "../constants.h"
#include <list>
#include <SFML/Graphics.hpp>

class World {
public:
    World();

    ~World();

    void mapOverItems(const std::function<void(WorldItem *)> &fun);

    void addItem(WorldItem *_item, sf::Vector2u pos);

    const WorldItem *getItem(sf::Vector2u pos);

    bool isItemAtPos(sf::Vector2u pos);

    void populateRandomly(unsigned int population);

    void depopulate();

private:
    WorldItem *items[WORLD_SIZE][WORLD_SIZE];
};


#endif //MACHINELEARNINGEXPERIMENTS_WORLD_H
