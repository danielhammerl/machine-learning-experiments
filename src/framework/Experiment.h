//
// Created by Daniel Hammerl on 02.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_EXPERIMENT_H
#define MACHINELEARNINGEXPERIMENTS_EXPERIMENT_H

#include <SFML/Graphics.hpp>
#include "engine/world/World.h"
#include <set>

class Experiment {
public:
    Experiment();
    virtual void endGeneration(World *world);

    unsigned int maxNumberOfBeings = 4000;
    unsigned int numberOfRoundsPerGeneration = 1000;
    unsigned int maxNumberOfGenerations = 1000;
    std::set<unsigned int> generationsToRender = {};
    float mutationRate = 0.05;

private:
};


#endif //MACHINELEARNINGEXPERIMENTS_EXPERIMENT_H
