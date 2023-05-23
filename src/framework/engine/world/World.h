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
    World(unsigned int _numberOfRoundsPerGeneration);

    ~World();

    void mapOverItems(const std::function<void(WorldItem *)> &fun);
    void mapOverItems(const std::function<void(WorldItem *, int)> &fun);

    void addItem(WorldItem *_item, sf::Vector2u pos);

    const WorldItem *getItem(sf::Vector2u pos);

    bool isItemAtPos(sf::Vector2u pos);

    void populateRandomly(unsigned int population);

    void populateByGenomes(std::vector<std::string> genomes, unsigned int population, float mutationRate);

    void depopulate();

    void round();

    void moveItem(WorldItem *item, MOVE_DIRECTION direction);

    void deleteItem(sf::Vector2u pos);

    unsigned int getNumberOfPopulation();

private:
    WorldItem *items[WORLD_SIZE][WORLD_SIZE];
    unsigned int numberOfRoundsPerGeneration;
};


#endif //MACHINELEARNINGEXPERIMENTS_WORLD_H
