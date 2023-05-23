//
// Created by Daniel Hammerl on 01.05.23.
//

#include "WorldItem.h"
#include "../constants.h"
#include <cmath>

WorldItem::WorldItem(unsigned int _numberOfRoundsPerGeneration) {
    auto numberOfHiddenNeuronsInFirstLayer = static_cast<NEURON_COUNT_TYPE>(std::round(
            static_cast<long double>(NUMBER_OF_INPUT_NEURONS) / 2));
    brain = new NeuronalNetwork(NUMBER_OF_INPUT_NEURONS, {numberOfHiddenNeuronsInFirstLayer},
                                NUMBER_OF_OUTPUT_NEURONS);
    brain->generateRandomWeights();
    numberOfRoundsPerGeneration = _numberOfRoundsPerGeneration;
}


WorldItem::WorldItem(unsigned int _numberOfRoundsPerGeneration, Genome genome) {
    auto numberOfHiddenNeuronsInFirstLayer = static_cast<NEURON_COUNT_TYPE>(std::round(
            static_cast<long double>(NUMBER_OF_INPUT_NEURONS) / 2));
    brain = new NeuronalNetwork(NUMBER_OF_INPUT_NEURONS, {numberOfHiddenNeuronsInFirstLayer},
                                NUMBER_OF_OUTPUT_NEURONS);

    genome.toNeuronalNetwork(*brain);
    numberOfRoundsPerGeneration = _numberOfRoundsPerGeneration;
}

WorldItem::~WorldItem() {
    delete brain;
    brain = nullptr;
}

void WorldItem::setPosition(sf::Vector2u pos) {
    this->position.x = pos.x;
    this->position.y = pos.y;
}

sf::Color WorldItem::getColor() {
    return sf::Color::Red;
}

sf::Vector2u WorldItem::getPosition() {
    return this->position;
}

void WorldItem::move(MOVE_DIRECTION direction) {
    WorldItemAction action;

    switch (direction) {
        case MOVE_DIRECTION::DOWN:
            action = WorldItemAction::MOVE_DOWN;
            break;
        case MOVE_DIRECTION::UP:
            action = WorldItemAction::MOVE_UP;
            break;
        case MOVE_DIRECTION::LEFT:
            action = WorldItemAction::MOVE_LEFT;
            break;
        case MOVE_DIRECTION::RIGHT:
            action = WorldItemAction::MOVE_RIGHT;
            break;
    }

    setNextAction(action);
}

void WorldItem::round(bool canMoveLeft, bool canMoveRight, bool canMoveUp, bool canMoveDown) {
    auto result = brain->feedForward(getSensorData(canMoveLeft, canMoveRight, canMoveUp, canMoveDown));
    double biggestValue = result[0];
    auto action = static_cast<WorldItemAction>(0);
    for (auto x = 0; x < result.size(); x++) {
        if (result[x] > biggestValue) {
            biggestValue = result[x];
            action = static_cast<WorldItemAction>(x);
        }
    }

    switch (action) {
        case WorldItemAction::MOVE_DOWN:
            this->move(MOVE_DIRECTION::DOWN);
            break;
        case WorldItemAction::MOVE_UP:
            this->move(MOVE_DIRECTION::UP);
            break;
        case WorldItemAction::MOVE_LEFT:
            this->move(MOVE_DIRECTION::LEFT);
            break;
        case WorldItemAction::MOVE_RIGHT:
            this->move(MOVE_DIRECTION::RIGHT);
            break;
        case WorldItemAction::NOOP_MAX_VALUE:
            throw std::logic_error(
                    "this should never happen -> neuron network has neuron for WorldItemAction::NOOP_MAX_VALUE");
    }

    currentRound++;
}

std::vector<double> WorldItem::getSensorData(bool canMoveLeft, bool canMoveRight, bool canMoveUp, bool canMoveDown) {
    std::vector<double> data;
    data.resize(static_cast<int>(WorldItemSensor::NOOP_MAX_VALUE));

    data[static_cast<int>(WorldItemSensor::CAN_MOVE_DOWN)] = canMoveDown ? 4 : -4;
    data[static_cast<int>(WorldItemSensor::CAN_MOVE_UP)] = canMoveUp ? 4 : -4;
    data[static_cast<int>(WorldItemSensor::CAN_MOVE_LEFT)] = canMoveLeft ? 4 : -4;
    data[static_cast<int>(WorldItemSensor::CAN_MOVE_RIGHT)] = canMoveRight ? 4 : -4;
    data[static_cast<int>(WorldItemSensor::RANDOM)] = getRandomDouble(-4, 4);
    data[static_cast<int>(WorldItemSensor::X_POS)] = (this->getPosition().x / WORLD_SIZE) * 8 - 4;
    data[static_cast<int>(WorldItemSensor::Y_POS)] = (this->getPosition().y / WORLD_SIZE) * 8 - 4;
    data[static_cast<int>(WorldItemSensor::ROUND)] =
            (static_cast<double>(currentRound) / static_cast<double>(numberOfRoundsPerGeneration)) * 8 - 4;

    return data;
}

std::string WorldItem::getGenomeAsString() {
    auto *genome = new Genome(*brain);
    std::string result = genome->toString();
    delete genome;
    return result;
}
