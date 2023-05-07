//
// Created by Daniel Hammerl on 01.05.23.
//

#include "World.h"
#include "../../Utils.h"
#include <iostream>

World::World() {

}

World::~World() {

}

void World::mapOverItems(const std::function<void(WorldItem *)> &fun) {
    for (auto &x: items) {
        for (auto &item: x) {
            if (item != nullptr) {
                fun(item);
            }
        }
    }
}

void World::addItem(WorldItem *_item, sf::Vector2u pos) {
    auto location = items[pos.x][pos.y];
    if (location == nullptr) {
        _item->setPosition(pos);
        items[pos.x][pos.y] = _item;
    } else {
        std::throw_with_nested(std::invalid_argument("cannot addItem to world - already item on position"));
    }
}

const WorldItem *World::getItem(sf::Vector2u pos) {
    return items[pos.x][pos.y];
}

void World::populateRandomly(unsigned int population) {
    for (auto x = 0; x < population; x++) {
        bool success = false;
        while (!success) {
            sf::Vector2u randomPos = sf::Vector2u(getRandomUnsignedInt(0, WORLD_SIZE),
                                                  getRandomUnsignedInt(0, WORLD_SIZE));
            if (isItemAtPos(randomPos)) {
                break;
            }
            addItem(new WorldItem(), randomPos);
            success = true;
        }
    }
}

bool World::isItemAtPos(sf::Vector2u pos) {
    return items[pos.x][pos.y] != nullptr;
}

void World::depopulate() {
    mapOverItems([&, this](WorldItem *item) {
        this->items[item->getPosition().x][item->getPosition().y] = nullptr;
        delete item;
    });
}
