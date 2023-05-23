//
// Created by Daniel Hammerl on 02.05.23.
//

#include "Test.h"
#include <iostream>

Test::Test() {
    this->maxNumberOfBeings = 1000;
    this->numberOfRoundsPerGeneration = 200;
    this->maxNumberOfGenerations = 1500;
    this->mutationRate = 0.05;
    this->generationsToRender = { 500, 1499};
}

void Test::endGeneration(World *world) {
    Experiment::endGeneration(world);

    world->mapOverItems([&, this](WorldItem *item) {
        if (item->getPosition().x < WORLD_SIZE - WORLD_SIZE / 4 ||
            item->getPosition().y < WORLD_SIZE - WORLD_SIZE / 4) {
            world->deleteItem(item->getPosition());
        }
    });
}
