//
// Created by Daniel Hammerl on 22.05.23.
//

#include "Genome.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <deque>

Genome::Genome(const NeuronalNetwork &brain) {
    if (brain.getNumberOfHiddenNeurons().size() != 1) {
        throw std::logic_error("Genome only can handle one hidden layer");
    }

    auto weightsBetweenInputNeuronsAndHiddenLayer = brain.getWeightsBetweenInputNeuronsAndHiddenLayer();
    auto weightsBetweenHiddenLayerAndOutputNeurons = brain.getWeightsBetweenHiddenLayerAndOutputNeurons();

    std::stringstream stream;
    for (const auto &inputNeuron: weightsBetweenInputNeuronsAndHiddenLayer) {
        for (auto weight: inputNeuron) {
            auto convertedWeight = convertWeightToInt32(weight);

            stream << std::setfill('0') << std::setw(sizeof(convertedWeight) * 2) << std::hex << convertedWeight;
        }
    }

    for (const auto &hiddenLayer: weightsBetweenHiddenLayerAndOutputNeurons) {
        for (auto weight: hiddenLayer) {
            auto convertedWeight = convertWeightToInt32(weight);

            stream << std::setfill('0') << std::setw(sizeof(convertedWeight) * 2) << std::hex << convertedWeight;
        }
    }

    genome = stream.str();
}

Genome::Genome(const std::string &from) {
    genome = from;
}

void Genome::mutateGenome(float rate) {
    if (rate > 1 || rate < 0) {
        throw std::invalid_argument("mutateGenome -> rate have to be between 0 and 1");
    }

    auto genomeAsBoolVector = hexStringToVector(genome);
    auto lengthOfVector = genomeAsBoolVector.size();
    auto numberOfMutations = static_cast<int>(static_cast<float>(lengthOfVector) * rate);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, genomeAsBoolVector.size() - 1);

    for (int i = 0; i < numberOfMutations; ++i) {
        int index = distribution(gen);
        genomeAsBoolVector[index] = !genomeAsBoolVector[index];
    }

    genome = vectorToHexString(genomeAsBoolVector);
}

void Genome::toNeuronalNetwork(NeuronalNetwork &brain) {
    int chunkSize = sizeof(int32_t) * 2;
    std::deque<double> values;
    for (size_t i = 0; i < genome.length(); i += chunkSize) {
        std::string chunk;
        chunk = genome.substr(i, chunkSize);
        int32_t value = static_cast<int32_t>(std::stoul(chunk, nullptr, 16));
        values.push_back(value);
    }

    auto weightsBetweenInputNeuronsAndHiddenLayer = brain.getWeightsBetweenInputNeuronsAndHiddenLayer();
    auto weightsBetweenHiddenLayerAndOutputNeurons = brain.getWeightsBetweenHiddenLayerAndOutputNeurons();

    for (int inputNeuronIndex = 0; inputNeuronIndex < weightsBetweenInputNeuronsAndHiddenLayer.size(); inputNeuronIndex++) {
       for(int hiddenNeuronIndex = 0; hiddenNeuronIndex < weightsBetweenInputNeuronsAndHiddenLayer[inputNeuronIndex].size(); hiddenNeuronIndex++) {
           brain.setWeightInputToHidden(inputNeuronIndex, hiddenNeuronIndex, convertInt32ToWeight(values[0]));
           values.pop_front();
       }
    }

    for(int hiddenNeuronIndex = 0; hiddenNeuronIndex < weightsBetweenHiddenLayerAndOutputNeurons.size(); hiddenNeuronIndex++) {
        for(int outputNeuronIndex = 0; outputNeuronIndex < weightsBetweenHiddenLayerAndOutputNeurons[hiddenNeuronIndex].size(); outputNeuronIndex++) {
            brain.setWeightHiddenToOutput(hiddenNeuronIndex, outputNeuronIndex, convertInt32ToWeight(values[0]));
            values.pop_front();
        }
    }

    if(values.size() != 0) {
        throw std::logic_error("there are unused parts of genome");
    }
}
