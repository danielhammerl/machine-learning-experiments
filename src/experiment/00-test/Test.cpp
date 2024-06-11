//
// Created by Daniel Hammerl on 02.05.23.
//

#include "Test.h"
#include <iostream>

Test::Test() {
    this->maxNumberOfBeings = 1000;
    this->numberOfRoundsPerGeneration = 250;
    this->maxNumberOfGenerations = 4000;
    this->mutationRate = 0.005;
    this->generationsToRender = {4000};
    this->reproducionRate = 5;
}

void Test::endGeneration(World *world) {
    Experiment::endGeneration(world);

    world->mapOverItems([&, this](WorldItem *item) {
        if (item->getPosition().x < WORLD_SIZE - WORLD_SIZE / 7 ||
            item->getPosition().y < WORLD_SIZE - WORLD_SIZE / 7) {
            world->deleteItem(item->getPosition());
        }
    });
}
