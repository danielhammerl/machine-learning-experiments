#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <filesystem>
#include <cmath>

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
    return x > 0 ? 1 : 0;
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

#endif