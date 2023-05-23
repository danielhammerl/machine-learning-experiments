//
// Created by Daniel Hammerl on 02.05.23.
//

#include "Test.h"
#include <iostream>

Test::Test() {
    this->maxNumberOfBeings = 1000;
    this->numberOfRoundsPerGeneration = 200;
    this->maxNumberOfGenerations = 10;
    this->generationsToRender = {1, 10};
}

void Test::endGeneration(World *world) {
    Experiment::endGeneration(world);

    world->mapOverItems([&, this](WorldItem *item) {
        if (item->getPosition().x > WORLD_SIZE / 2) {
            world->deleteItem(item->getPosition());
        }
    });
}
