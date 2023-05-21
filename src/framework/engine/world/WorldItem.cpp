//
// Created by Daniel Hammerl on 01.05.23.
//

#include "WorldItem.h"

WorldItem::WorldItem() {
    brain = new NeuronalNetwork(1, {1}, 4);
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
            action = MOVE_DOWN;
            break;
        case MOVE_DIRECTION::UP:
            action = MOVE_UP;
            break;
        case MOVE_DIRECTION::LEFT:
            action = MOVE_LEFT;
            break;
        case MOVE_DIRECTION::RIGHT:
            action = MOVE_RIGHT;
            break;
        case MOVE_DIRECTION::UP_LEFT:
            action = MOVE_LEFT_UP;
            break;
        case MOVE_DIRECTION::UP_RIGHT:
            action = MOVE_RIGHT_UP;
            break;
        case MOVE_DIRECTION::DOWN_LEFT:
            action = MOVE_LEFT_DOWN;
            break;
        case MOVE_DIRECTION::DOWN_RIGHT:
            action = MOVE_RIGHT_DOWN;
            break;
    }

    setNextAction(action);
}

void WorldItem::round() {
    auto result = brain->feedForward({getRandomDouble(-5, 5)});
    double biggestValue = result[0];
    int indexWithBiggestValue = 0;
    for (auto x = 0; x < result.size(); x++) {
        if (result[x] > biggestValue) {
            biggestValue = result[x];
            indexWithBiggestValue = x;
        }
    }

    switch (indexWithBiggestValue) {
        case 0:
            this->move(MOVE_DIRECTION::DOWN);
            break;
        case 1:
            this->move(MOVE_DIRECTION::UP);
            break;
        case 2:
            this->move(MOVE_DIRECTION::LEFT);
            break;
        case 3:
            this->move(MOVE_DIRECTION::RIGHT);
            break;
        default:
            break;
    }
}
