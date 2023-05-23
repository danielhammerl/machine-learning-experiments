//
// Created by Daniel Hammerl on 07.05.23.
//

#include "NeuronalNetwork.h"
#include <iostream>

NeuronalNetwork::NeuronalNetwork(NEURON_COUNT_TYPE _numberOfInputNeurons, std::vector<NEURON_COUNT_TYPE> _hiddenLayers,
                                 NEURON_COUNT_TYPE _numberOfOutputNeurons) {

    if (_hiddenLayers.empty()) {
        throw std::invalid_argument("NeuronalNetwork does not support zero hidden layers!");
    }

    inputNeurons.resize(_numberOfInputNeurons, 0);
    outputNeurons.resize(_numberOfOutputNeurons, 0);

    for (unsigned int numberOfNodesInLayer: _hiddenLayers) {
        std::vector<double> temp;
        temp.resize(numberOfNodesInLayer, 0);
        hiddenLayers.push_back(temp);
    }

    for (unsigned inputNeuronIndex = 0; inputNeuronIndex < inputNeurons.size(); inputNeuronIndex++) {
        std::vector<double> temp;
        temp.reserve(hiddenLayers[0].size());
        for (unsigned hiddenNeuronInFirstLayerIndex = 0;
             hiddenNeuronInFirstLayerIndex < hiddenLayers[0].size(); hiddenNeuronInFirstLayerIndex++) {
            temp.push_back(0);
        }
        weightBetweenInputNeuronsAndHiddenLayer.push_back(temp);
    }

    // -1 because we dont want the connection between last layer and output layer here
    for (unsigned hiddenLayerIndex = 0; hiddenLayerIndex < hiddenLayers.size() - 1; hiddenLayerIndex++) {
        std::vector<std::vector<double>> temp;
        for (unsigned hiddenNeuronIndex = 0;
             hiddenNeuronIndex < hiddenLayers[hiddenLayerIndex].size(); hiddenNeuronIndex++) {
            std::vector<double> temp2;
            temp2.resize(hiddenLayers[hiddenLayerIndex + 1].size(), 0);
            temp.push_back(temp2);
        }
        weightBetweenHiddenLayers.push_back(temp);
    }

    for (unsigned hiddenNeuronLastLayerIndex = 0;
         hiddenNeuronLastLayerIndex < hiddenLayers.back().size(); hiddenNeuronLastLayerIndex++) {
        std::vector<double> temp;
        temp.resize(outputNeurons.size(), 0);
        weightBetweenHiddenLayerAndOutputNeurons.push_back(temp);
    }

}

void NeuronalNetwork::generateRandomWeights() {
    for (auto &inputNeuron: weightBetweenInputNeuronsAndHiddenLayer) {
        for (auto &connection: inputNeuron) {
            connection = getRandomDouble(MIN_NEURON_WEIGHT, MAX_NEURON_WEIGHT);
        }
    }

    for (auto &hiddenLayer: weightBetweenHiddenLayers) {
        for (auto &hiddenNode: hiddenLayer) {
            for (auto &connection: hiddenNode) {
                connection = getRandomDouble(MIN_NEURON_WEIGHT, MAX_NEURON_WEIGHT);
            }
        }
    }

    for (auto &outputNeuron: weightBetweenHiddenLayerAndOutputNeurons) {
        for (auto &connection: outputNeuron) {
            connection = getRandomDouble(MIN_NEURON_WEIGHT, MAX_NEURON_WEIGHT);
        }
    }
}

void NeuronalNetwork::printWeights() {
    std::cout << "Printing Neuron Network" << std::endl;

    for (const auto &inputNeuron: weightBetweenInputNeuronsAndHiddenLayer) {
        std::cout << "input neuron x to next hidden neurons ";
        for (auto connection: inputNeuron) {
            std::cout << connection << " ";
        }
        std::cout << std::endl;
    }

    for (const auto &hiddenLayer: weightBetweenHiddenLayers) {
        for (const auto &hiddenNode: hiddenLayer) {
            std::cout << "hidden neuron to next hidden neurons ";
            for (auto connection: hiddenNode) {
                std::cout << connection << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    for (const auto &outputNeuron: weightBetweenHiddenLayerAndOutputNeurons) {
        std::cout << "hidden neuron x in last layer to output neurons ";
        for (auto connection: outputNeuron) {
            std::cout << connection << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Finished printing Neuron Network" << std::endl;
}

void
NeuronalNetwork::setWeightInputToHidden(NEURON_COUNT_TYPE indexOfInputNeuron, NEURON_COUNT_TYPE indexOfHiddenNeuron,
                                        WEIGHT_VALUE_TYPE weight) {
    weightBetweenInputNeuronsAndHiddenLayer[indexOfInputNeuron][indexOfHiddenNeuron] = weight;
}

void
NeuronalNetwork::setWeightHiddenToHidden(NEURON_COUNT_TYPE indexOfLeftHiddenLayer, NEURON_COUNT_TYPE indexOfLeftNeuron,
                                         NEURON_COUNT_TYPE indexOfRightNeuron, WEIGHT_VALUE_TYPE weight) {
    weightBetweenHiddenLayers[indexOfLeftHiddenLayer][indexOfLeftNeuron][indexOfRightNeuron] = weight;
}

void
NeuronalNetwork::setWeightHiddenToOutput(NEURON_COUNT_TYPE indexOfHiddenNeuron, NEURON_COUNT_TYPE indexOfOutputNeuron,
                                         WEIGHT_VALUE_TYPE weight) {
    weightBetweenHiddenLayerAndOutputNeurons[indexOfHiddenNeuron][indexOfOutputNeuron] = weight;
}

std::vector<double> NeuronalNetwork::feedForward(std::vector<NEURON_VALUE_TYPE> input) {
    if (input.size() != inputNeurons.size()) {
        throw std::invalid_argument(
                "NeuronalNetwork::feedForward -> number of inputs should have length of number of input neurons");
    }
    for (unsigned hiddenNeuronIndexInFirstLayer = 0;
         hiddenNeuronIndexInFirstLayer < hiddenLayers[0].size(); hiddenNeuronIndexInFirstLayer++) {
        double activation = 0;

        for (int inputIndex = 0; inputIndex < inputNeurons.size(); inputIndex++) {
            activation +=
                    input[inputIndex] *
                    weightBetweenInputNeuronsAndHiddenLayer[inputIndex][hiddenNeuronIndexInFirstLayer];
        }

        hiddenLayers[0][hiddenNeuronIndexInFirstLayer] = ACTIVATION_FUNCTION(activation - GLOBAL_BIAS);
    }

    for (unsigned hiddenLayerIndex = 1; hiddenLayerIndex < hiddenLayers.size(); hiddenLayerIndex++) {
        for (unsigned hiddenNeuronIndex = 0;
             hiddenNeuronIndex < hiddenLayers[hiddenLayerIndex].size(); hiddenNeuronIndex++) {

            double activation = 0;

            for (unsigned hiddenNeuronIndexInLayerBefore = 0; hiddenNeuronIndexInLayerBefore <
                                                              hiddenLayers[hiddenLayerIndex -
                                                                           1].size(); hiddenNeuronIndexInLayerBefore++) {
                activation += hiddenLayers[hiddenLayerIndex - 1][hiddenNeuronIndexInLayerBefore] *
                              weightBetweenHiddenLayers[hiddenLayerIndex -
                                                        1][hiddenNeuronIndexInLayerBefore][hiddenNeuronIndex];
            }

            hiddenLayers[hiddenLayerIndex][hiddenNeuronIndex] = ACTIVATION_FUNCTION(activation - GLOBAL_BIAS);
        }
    }
    for (unsigned outputNeuronIndex = 0; outputNeuronIndex < outputNeurons.size(); outputNeuronIndex++) {
        double activation = 0;
        for (unsigned hiddenNeuronLastLayerIndex = 0;
             hiddenNeuronLastLayerIndex < hiddenLayers[0].size(); hiddenNeuronLastLayerIndex++) {

            activation += hiddenLayers.back()[hiddenNeuronLastLayerIndex] *
                          weightBetweenHiddenLayerAndOutputNeurons[hiddenNeuronLastLayerIndex][outputNeuronIndex];
        }

        outputNeurons[outputNeuronIndex] = ACTIVATION_FUNCTION(activation - GLOBAL_BIAS);
    }

    return outputNeurons;
}

unsigned char NeuronalNetwork::getNumberOfInputNeurons() const {
    return inputNeurons.size();
}

unsigned char NeuronalNetwork::getNumberOfOutputNeurons() const {
    return outputNeurons.size();
}


std::vector<unsigned char> NeuronalNetwork::getNumberOfHiddenNeurons() const {
    std::vector<unsigned char> temp;
    temp.reserve(hiddenLayers.size());
    for (const auto &it: hiddenLayers) {
        temp.push_back(it.size());
    }
    return temp;
}

std::vector<std::vector<double>> NeuronalNetwork::getWeightsBetweenInputNeuronsAndHiddenLayer() const {
    return weightBetweenInputNeuronsAndHiddenLayer;
}

std::vector<std::vector<std::vector<double>>> NeuronalNetwork::getWeightsBetweenHiddenLayers() const {
    return weightBetweenHiddenLayers;
}

std::vector<std::vector<double>> NeuronalNetwork::getWeightsBetweenHiddenLayerAndOutputNeurons() const {
    return weightBetweenHiddenLayerAndOutputNeurons;
}