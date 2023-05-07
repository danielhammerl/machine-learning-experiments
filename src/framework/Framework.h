//
// Created by Daniel Hammerl on 01.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_FRAMEWORK_H
#define MACHINELEARNINGEXPERIMENTS_FRAMEWORK_H

#include <SFML/Graphics.hpp>
#include "Experiment.h"

class Framework {
public:
    Framework() = delete;

    Framework(Experiment *_experiment, int argc, char **argv);

    ~Framework();

    void run();

    void startGeneration();
    void endGeneration();

    void round();
    void render();

private:
    Experiment *experiment;
    World *world;

    unsigned int currentRound = 1;
    unsigned int currentGeneration = 1;

};


#endif //MACHINELEARNINGEXPERIMENTS_FRAMEWORK_H
