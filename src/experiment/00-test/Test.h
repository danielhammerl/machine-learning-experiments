//
// Created by Daniel Hammerl on 02.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_TEST_H
#define MACHINELEARNINGEXPERIMENTS_TEST_H


#include "../../framework/Experiment.h"

class Test : public Experiment {
public:

Test();
void endGeneration(World *world) override;

};


#endif //MACHINELEARNINGEXPERIMENTS_TEST_H
