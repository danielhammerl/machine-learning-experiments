//
// Created by Daniel Hammerl on 01.05.23.
//

#include "WorldItem.h"

WorldItem::WorldItem() {
    brain = new NeuronalNetwork(static_cast<int>(WorldItemSensor::NOOP_MAX_VALUE), {1},
                                static_cast<int>(WorldItemAction::NOOP_MAX_VALUE));
    brain->generateRandomWeights();
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
        case MOVE_DIRECTION::UP_LEFT:
            action = WorldItemAction::MOVE_LEFT_UP;
            break;
        case MOVE_DIRECTION::UP_RIGHT:
            action = WorldItemAction::MOVE_RIGHT_UP;
            break;
        case MOVE_DIRECTION::DOWN_LEFT:
            action = WorldItemAction::MOVE_LEFT_DOWN;
            break;
        case MOVE_DIRECTION::DOWN_RIGHT:
            action = WorldItemAction::MOVE_RIGHT_DOWN;
            break;
    }

    setNextAction(action);
}

void WorldItem::round() {
    auto result = brain->feedForward(getSensorData());
    double biggestValue = result[0];
    auto action = static_cast<WorldItemAction>(0);
    for (auto x = 0; x < result.size(); x++) {
        if (result[x] > biggestValue) {
            biggestValue = result[x];
            action = static_cast<WorldItemAction>(x);
        }
    }

    switch (action) {
        case WorldItemAction::MOVE_LEFT_DOWN:
            this->move(MOVE_DIRECTION::DOWN_LEFT);
            break;
        case WorldItemAction::MOVE_LEFT_UP:
            this->move(MOVE_DIRECTION::UP_LEFT);
            break;
        case WorldItemAction::MOVE_RIGHT_DOWN:
            this->move(MOVE_DIRECTION::DOWN_RIGHT);
            break;
        case WorldItemAction::MOVE_RIGHT_UP:
            this->move(MOVE_DIRECTION::UP_RIGHT);
            break;
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
}

std::vector<double> WorldItem::getSensorData() {
    std::vector<double> data;
    data.resize(static_cast<int>(WorldItemSensor::NOOP_MAX_VALUE));

    data[static_cast<int>(WorldItemSensor::RANDOM)] = getRandomDouble(-5, 5);

    return data;
}
