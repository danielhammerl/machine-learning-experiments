//
// Created by Daniel Hammerl on 22.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_GENOME_H
#define MACHINELEARNINGEXPERIMENTS_GENOME_H

#include <string>
#include "../NeuronalNetwork.h"

class Genome {
public:
    Genome() = delete;
    explicit Genome(const NeuronalNetwork &brain);
    explicit Genome(const std::string &from);

    std::string toString() const {
        return genome;
    }

    void mutateGenome(float rate);
    void toNeuronalNetwork(NeuronalNetwork &brain);

private:
    std::string genome = "";


};


#endif //MACHINELEARNINGEXPERIMENTS_GENOME_H
