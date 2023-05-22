//
// Created by Daniel Hammerl on 07.05.23.
//

#include "NeuronalNetwork.h"
#include <iostream>

NeuronalNetwork::NeuronalNetwork(unsigned _numberOfInputNeurons, std::vector<unsigned> _hiddenLayers,
                                 unsigned _numberOfOutputNeurons) {

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
            connection = getRandomDouble(MIN_WEIGHT, MAX_WEIGHT);
        }
    }

    for (auto &hiddenLayer: weightBetweenHiddenLayers) {
        for (auto &hiddenNode: hiddenLayer) {
            for (auto &connection: hiddenNode) {
                connection = getRandomDouble(MIN_WEIGHT, MAX_WEIGHT);
            }
        }
    }

    for (auto &outputNeuron: weightBetweenHiddenLayerAndOutputNeurons) {
        for (auto &connection: outputNeuron) {
            connection = getRandomDouble(MIN_WEIGHT, MAX_WEIGHT);
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

void NeuronalNetwork::setWeightInputToHidden(unsigned int indexOfInputNeuron, unsigned int indexOfHiddenNeuron,
                                             WEIGHT_VALUE weight) {
    weightBetweenInputNeuronsAndHiddenLayer[indexOfInputNeuron][indexOfHiddenNeuron] = weight;
}

void NeuronalNetwork::setWeightHiddenToHidden(unsigned int indexOfLeftHiddenLayer, unsigned int indexOfLeftNeuron,
                                              unsigned int indexOfRightNeuron, WEIGHT_VALUE weight) {
    weightBetweenHiddenLayers[indexOfLeftHiddenLayer][indexOfLeftNeuron][indexOfRightNeuron] = weight;
}

void NeuronalNetwork::setWeightHiddenToOutput(unsigned int indexOfHiddenNeuron, unsigned int indexOfOutputNeuron,
                                              WEIGHT_VALUE weight) {
    weightBetweenHiddenLayerAndOutputNeurons[indexOfHiddenNeuron][indexOfOutputNeuron] = weight;
}

std::vector<double> NeuronalNetwork::feedForward(std::vector<NEURON_VALUE> input) {
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

unsigned NeuronalNetwork::getNumberOfInputNeurons() const {
    return inputNeurons.size();
}

unsigned NeuronalNetwork::getNumberOfOutputNeurons() const {
    return outputNeurons.size();
}


std::vector<unsigned> NeuronalNetwork::getNumberOfHiddenNeurons() const {
    std::vector<unsigned> temp;
    temp.reserve(hiddenLayers.size());
    for (const auto &it: hiddenLayers) {
        temp.push_back(it.size());
    }
    return temp;
}

std::vector<std::vector<double>> NeuronalNetwork::getWeightBetweenInputNeuronsAndHiddenLayer() const {
    return weightBetweenInputNeuronsAndHiddenLayer;
}

std::vector<std::vector<std::vector<double>>> NeuronalNetwork::getWeightBetweenHiddenLayers() const {
    return weightBetweenHiddenLayers;
}

std::vector<std::vector<double>> NeuronalNetwork::getWeightBetweenHiddenLayerAndOutputNeurons() const {
    return weightBetweenHiddenLayerAndOutputNeurons;
}