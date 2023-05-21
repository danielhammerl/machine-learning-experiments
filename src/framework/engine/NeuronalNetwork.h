//
// Created by Daniel Hammerl on 07.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_NEURONALNETWORK_H
#define MACHINELEARNINGEXPERIMENTS_NEURONALNETWORK_H

#include <vector>
#include <functional>
#include "../Utils.h"

class NeuronalNetwork {
public:
    NeuronalNetwork(unsigned _numberOfInputNeurons, std::vector<unsigned> _hiddenLayers,
                    unsigned _numberOfOutputNeurons);

    void generateRandomWeights();

    void printWeights();

    void setWeightInputToHidden(unsigned indexOfInputNeuron, unsigned indexOfHiddenNeuron,
                                double weight);

    void
    setWeightHiddenToHidden(unsigned indexOfLeftHiddenLayer, unsigned indexOfLeftNeuron, unsigned indexOfRightNeuron,
                            double weight);

    void setWeightHiddenToOutput(unsigned indexOfHiddenNeuron, unsigned indexOfOutputNeuron,
                                 double weight);

    std::vector<double> feedForward(std::vector<double> input);

private:
    const double GLOBAL_BIAS = 0.1;
    //const double LEARNING_RATE = 0.1;
    const double RANDOM_WEIGHT_MIN = -15;
    const double RANDOM_WEIGHT_MAX = 15;

    const std::function<double(double)> ACTIVATION_FUNCTION = sigmoidFunction;
    const std::function<double(double)> ACTIVATION_FUNCTION_DERIVATIVE = sigmoidDerivativeFunction;

    std::vector<double> inputNeurons;
    std::vector<double> outputNeurons;
    std::vector<std::vector<double>> hiddenLayers;

    std::vector<std::vector<double>> weightBetweenInputNeuronsAndHiddenLayer; // [inputIndex][hiddenInFirstLayerIndex]
    std::vector<std::vector<std::vector<double>>> weightBetweenHiddenLayers; // [indexOfLeftHiddenLayer][indexOfLeftNode][indexOfRightNode]
    std::vector<std::vector<double>> weightBetweenHiddenLayerAndOutputNeurons; // [hiddenInLastLayerIndex][outputIndex]
};


#endif //MACHINELEARNINGEXPERIMENTS_NEURONALNETWORK_H
