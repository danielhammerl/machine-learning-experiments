#include <random>
#include <filesystem>

static unsigned int getRandomUnsignedInt(unsigned int min, unsigned int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

static void createDirectoryIfDoesntExist(const char *dirName) {
    if (!std::filesystem::is_directory(dirName) ||
        !std::filesystem::exists(dirName)) {
        std::filesystem::create_directory(dirName);
    }
}