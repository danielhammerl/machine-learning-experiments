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
    using NEURON_VALUE = double;
    using WEIGHT_VALUE = double;

    NeuronalNetwork(unsigned _numberOfInputNeurons, std::vector<unsigned> _hiddenLayers,
                    unsigned _numberOfOutputNeurons);

    void generateRandomWeights();

    void printWeights();

    void setWeightInputToHidden(unsigned indexOfInputNeuron, unsigned indexOfHiddenNeuron,
                                WEIGHT_VALUE weight);

    void
    setWeightHiddenToHidden(unsigned indexOfLeftHiddenLayer, unsigned indexOfLeftNeuron, unsigned indexOfRightNeuron,
                            WEIGHT_VALUE weight);

    void setWeightHiddenToOutput(unsigned indexOfHiddenNeuron, unsigned indexOfOutputNeuron,
                                 WEIGHT_VALUE weight);

    std::vector<NEURON_VALUE> feedForward(std::vector<NEURON_VALUE> input);

    [[nodiscard]] unsigned getNumberOfInputNeurons() const;

    [[nodiscard]] unsigned getNumberOfOutputNeurons() const;

    [[nodiscard]] std::vector<unsigned> getNumberOfHiddenNeurons() const;

    [[nodiscard]] std::vector<std::vector<WEIGHT_VALUE>> getWeightBetweenInputNeuronsAndHiddenLayer() const;

    [[nodiscard]] std::vector<std::vector<std::vector<WEIGHT_VALUE>>> getWeightBetweenHiddenLayers() const;

    [[nodiscard]] std::vector<std::vector<WEIGHT_VALUE>> getWeightBetweenHiddenLayerAndOutputNeurons() const;

    static constexpr double GLOBAL_BIAS = 0.1;
    static constexpr double MIN_WEIGHT = -4;
    static constexpr double MAX_WEIGHT = 4;
private:

    const std::function<NEURON_VALUE(NEURON_VALUE)> ACTIVATION_FUNCTION = sigmoidFunction;
    const std::function<NEURON_VALUE(NEURON_VALUE)> ACTIVATION_FUNCTION_DERIVATIVE = sigmoidDerivativeFunction;

    std::vector<NEURON_VALUE> inputNeurons;
    std::vector<NEURON_VALUE> outputNeurons;
    std::vector<std::vector<NEURON_VALUE>> hiddenLayers;

    std::vector<std::vector<WEIGHT_VALUE>> weightBetweenInputNeuronsAndHiddenLayer; // [inputIndex][hiddenInFirstLayerIndex]
    std::vector<std::vector<std::vector<WEIGHT_VALUE>>> weightBetweenHiddenLayers; // [indexOfLeftHiddenLayer][indexOfLeftNode][indexOfRightNode]
    std::vector<std::vector<WEIGHT_VALUE>> weightBetweenHiddenLayerAndOutputNeurons; // [hiddenInLastLayerIndex][outputIndex]
};


#endif //MACHINELEARNINGEXPERIMENTS_NEURONALNETWORK_H
