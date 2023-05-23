//
// Created by Daniel Hammerl on 02.05.23.
//

#include "Test.h"
#include <iostream>

Test::Test() {
    this->maxNumberOfBeings = 1000;
    this->numberOfRoundsPerGeneration = 400;
    this->maxNumberOfGenerations = 1200;
    this->mutationRate = 0.01;
    this->generationsToRender = { 1200};
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
