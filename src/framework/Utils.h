#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <filesystem>
#include <cmath>
#include <algorithm>

using NEURON_VALUE_TYPE = double;
using WEIGHT_VALUE_TYPE = double;
using NEURON_COUNT_TYPE = uint8_t;

static constexpr double MAX_NEURON_WEIGHT = 15;
static constexpr double MIN_NEURON_WEIGHT = -(MAX_NEURON_WEIGHT);

static double sigmoidFunction(double x) {
    return 1.f / (1.f + std::exp(-x));
}

static double sigmoidDerivativeFunction(double x) {
    return x * (1 - x);
}

static double reluFunction(double x) {
    return x > 0 ? x : 0;
}

static double reluDerivativeFunction(double x) {
    return x >= 0 ? 1 : 0;
}

static unsigned int getRandomUnsignedInt(unsigned int min, unsigned int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

static double getRandomDouble(double min, double max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(min, max);

    return dist(rng);
}

static double randomBetweenZeroAndOne() {
    return getRandomDouble(0, 1);
}

static void createDirectoryIfDoesntExist(const char *dirName) {
    if (!std::filesystem::is_directory(dirName) ||
        !std::filesystem::exists(dirName)) {
        std::filesystem::create_directory(dirName);
    }
}

// convert weight to int32_t to save some memory - now data is 4 bytes long instead of 8
static int32_t convertWeightToInt32(WEIGHT_VALUE_TYPE value) {
    // between -1 and 1
    auto normalizedValue = value >= 0 ? std::min(value / MAX_NEURON_WEIGHT, 1.) : std::max(
            value / MAX_NEURON_WEIGHT, -1.);

    if (normalizedValue >= 0) {
        return static_cast<int32_t>(static_cast<double>(std::numeric_limits<int32_t>::max()) * normalizedValue);
    }

    return static_cast<int32_t>(static_cast<double>(std::numeric_limits<int32_t>::min()) * std::abs(normalizedValue));
}

static WEIGHT_VALUE_TYPE convertInt32ToWeight(int32_t value) {
    if (value >= 0) {
        return (static_cast<double>(value) / static_cast<double>(std::numeric_limits<int32_t>::max())) *
               MAX_NEURON_WEIGHT;
    }

    return (static_cast<double>(value) / static_cast<double>(std::numeric_limits<int32_t>::min())) *
           MIN_NEURON_WEIGHT;
}

enum MOVE_DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
};

static std::vector<bool> hexStringToVector(const std::string &hexString) {
    std::vector<bool> result;

    for (char c: hexString) {
        int value;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            value = 10 + (c - 'a');
        } else if (c >= 'A' && c <= 'F') {
            value = 10 + (c - 'A');
        } else {
            throw std::invalid_argument("invalid hex string: " + hexString);
        }

        for (int i = 3; i >= 0; --i) {
            bool bit = (value >> i) & 1;
            result.push_back(bit);
        }
    }

    return result;
}

static std::string vectorToHexString(const std::vector<bool> &bitVector) {
    std::string result;
    size_t numBits = bitVector.size();

    if (numBits % 4 != 0) {
        throw std::invalid_argument("invalid bit vector: number of bits have to be multiple of 4");
    }

    for (size_t i = 0; i < numBits; i += 4) {
        int hexValue = 0;

        for (size_t j = 0; j < 4; ++j) {
            bool bit = bitVector[i + j];
            hexValue = (hexValue << 1) | bit;
        }

        if (hexValue < 10) {
            result += '0' + hexValue;
        } else {
            result += 'a' + (hexValue - 10);
        }
    }

    return result;
}


#endif