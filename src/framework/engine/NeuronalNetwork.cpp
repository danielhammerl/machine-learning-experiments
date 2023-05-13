//
// Created by Daniel Hammerl on 07.05.23.
//

#include "NeuronalNetwork.h"
#include "../Utils.h"
#include <iostream>

NeuronalNetwork::NeuronalNetwork(unsigned _numberOfInputNeurons, std::vector<unsigned> _hiddenLayers,
                                 unsigned _numberOfOutputNeurons)
        : numberOfInputNeurons(_numberOfInputNeurons),
          hiddenLayers(_hiddenLayers),
          numberOfOutputNeurons(_numberOfOutputNeurons) {

    if (hiddenLayers.empty()) {
        throw std::invalid_argument("NeuronalNetwork does not support zero hidden layers!");
    }

    for (unsigned inputNeuronIndex = 0; inputNeuronIndex < numberOfInputNeurons; inputNeuronIndex++) {
        std::vector<double> temp;
        temp.reserve(hiddenLayers[0]);
        for (unsigned hiddenNeuronInFirstLayerIndex = 0;
             hiddenNeuronInFirstLayerIndex < hiddenLayers[0]; hiddenNeuronInFirstLayerIndex++) {
            temp.push_back(0);
        }
        weightBetweenInputNeuronsAndHiddenLayer.push_back(temp);
    }

    // -1 because we dont want the connection between last layer and output layer here
    for (unsigned hiddenLayerIndex = 0; hiddenLayerIndex < hiddenLayers.size() - 1; hiddenLayerIndex++) {
        std::vector<std::vector<double>> temp;
        for (unsigned hiddenNeuronIndex = 0; hiddenNeuronIndex < hiddenLayers[hiddenLayerIndex]; hiddenNeuronIndex++) {
            std::vector<double> temp2;
            temp2.reserve(hiddenLayers[hiddenLayerIndex + 1]);
            for (unsigned nextHiddenNeuronIndex = 0;
                 nextHiddenNeuronIndex < hiddenLayers[hiddenLayerIndex + 1]; nextHiddenNeuronIndex++) {
                temp2.push_back(0);
            }
            temp.push_back(temp2);
        }
        weightBetweenHiddenLayers.push_back(temp);
    }

    for (unsigned hiddenNeuronLastLayerIndex = 0;
         hiddenNeuronLastLayerIndex < hiddenLayers.back(); hiddenNeuronLastLayerIndex++) {
        std::vector<double> temp;
        for (unsigned outputNeuronIndex = 0; outputNeuronIndex < numberOfOutputNeurons; outputNeuronIndex++) {
            temp.push_back(0);
        }
        weightBetweenHiddenLayerAndOutputNeurons.push_back(temp);
    }

}

void NeuronalNetwork::generateRandomWeights() {
    for (auto &inputNeuron: weightBetweenInputNeuronsAndHiddenLayer) {
        for (auto &connection: inputNeuron) {
            connection = randomBetweenZeroAndOne();
        }
    }

    for (auto &hiddenLayer: weightBetweenHiddenLayers) {
        for (auto &hiddenNode: hiddenLayer) {
            for (auto &connection: hiddenNode) {
                connection = randomBetweenZeroAndOne();
            }
        }
    }

    for (auto &outputNeuron: weightBetweenHiddenLayerAndOutputNeurons) {
        for (auto &connection: outputNeuron) {
            connection = randomBetweenZeroAndOne();
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
                                             double weight) {
    weightBetweenInputNeuronsAndHiddenLayer[indexOfInputNeuron][indexOfHiddenNeuron] = weight;
}

void NeuronalNetwork::setWeightHiddenToHidden(unsigned int indexOfLeftHiddenLayer, unsigned int indexOfLeftNeuron,
                                              unsigned int indexOfRightNeuron, double weight) {
    weightBetweenHiddenLayers[indexOfLeftHiddenLayer][indexOfLeftNeuron][indexOfRightNeuron] = weight;
}

void NeuronalNetwork::setWeightHiddenToOutput(unsigned int indexOfHiddenNeuron, unsigned int indexOfOutputNeuron,
                                              double weight) {
    weightBetweenHiddenLayerAndOutputNeurons[indexOfHiddenNeuron][indexOfOutputNeuron] = weight;
}

std::vector<double> NeuronalNetwork::feedForward(std::vector<double> input) {
    // TO IMPLEMENT
}

