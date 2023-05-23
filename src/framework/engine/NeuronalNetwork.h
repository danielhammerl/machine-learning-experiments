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
    NeuronalNetwork(NEURON_COUNT_TYPE _numberOfInputNeurons, std::vector<NEURON_COUNT_TYPE> _hiddenLayers,
                    NEURON_COUNT_TYPE _numberOfOutputNeurons);

    void generateRandomWeights();

    void printWeights();

    void setWeightInputToHidden(NEURON_COUNT_TYPE indexOfInputNeuron, NEURON_COUNT_TYPE indexOfHiddenNeuron,
                                WEIGHT_VALUE_TYPE weight);

    void
    setWeightHiddenToHidden(NEURON_COUNT_TYPE indexOfLeftHiddenLayer, NEURON_COUNT_TYPE indexOfLeftNeuron,
                            NEURON_COUNT_TYPE indexOfRightNeuron,
                            WEIGHT_VALUE_TYPE weight);

    void setWeightHiddenToOutput(NEURON_COUNT_TYPE indexOfHiddenNeuron, NEURON_COUNT_TYPE indexOfOutputNeuron,
                                 WEIGHT_VALUE_TYPE weight);

    std::vector<NEURON_VALUE_TYPE> feedForward(std::vector<NEURON_VALUE_TYPE> input);

    [[nodiscard]] NEURON_COUNT_TYPE getNumberOfInputNeurons() const;

    [[nodiscard]] NEURON_COUNT_TYPE getNumberOfOutputNeurons() const;

    [[nodiscard]] std::vector<NEURON_COUNT_TYPE> getNumberOfHiddenNeurons() const;

    [[nodiscard]] std::vector<std::vector<WEIGHT_VALUE_TYPE>> getWeightsBetweenInputNeuronsAndHiddenLayer() const;

    [[nodiscard]] std::vector<std::vector<std::vector<WEIGHT_VALUE_TYPE>>> getWeightsBetweenHiddenLayers() const;

    [[nodiscard]] std::vector<std::vector<WEIGHT_VALUE_TYPE>> getWeightsBetweenHiddenLayerAndOutputNeurons() const;

    static constexpr double GLOBAL_BIAS = 0.1;
private:

    const std::function<NEURON_VALUE_TYPE(NEURON_VALUE_TYPE)> ACTIVATION_FUNCTION = sigmoidFunction;
    const std::function<NEURON_VALUE_TYPE(
            NEURON_VALUE_TYPE)> ACTIVATION_FUNCTION_DERIVATIVE = sigmoidDerivativeFunction;

    std::vector<NEURON_VALUE_TYPE> inputNeurons;
    std::vector<NEURON_VALUE_TYPE> outputNeurons;
    std::vector<std::vector<NEURON_VALUE_TYPE>> hiddenLayers;

    std::vector<std::vector<WEIGHT_VALUE_TYPE>> weightBetweenInputNeuronsAndHiddenLayer; // [inputIndex][hiddenInFirstLayerIndex]
    std::vector<std::vector<std::vector<WEIGHT_VALUE_TYPE>>> weightBetweenHiddenLayers; // [indexOfLeftHiddenLayer][indexOfLeftNode][indexOfRightNode]
    std::vector<std::vector<WEIGHT_VALUE_TYPE>> weightBetweenHiddenLayerAndOutputNeurons; // [hiddenInLastLayerIndex][outputIndex]
};


#endif //MACHINELEARNINGEXPERIMENTS_NEURONALNETWORK_H
