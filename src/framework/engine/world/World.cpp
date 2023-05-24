//
// Created by Daniel Hammerl on 01.05.23.
//

#include "World.h"
#include <iostream>
#include <SFML/System.hpp>
#include <algorithm>
#include <cmath>

World::World(unsigned int _numberOfRoundsPerGeneration) {
    numberOfRoundsPerGeneration = _numberOfRoundsPerGeneration;
}

World::~World() {

}

//108 bei mutation rate 0.1
void World::round() {
    const int numberOfThreads = 12;
    std::array<std::list<WorldItem *>, numberOfThreads> items;
    items.fill(std::list<WorldItem *>());
    std::array<sf::Thread *, numberOfThreads> threads;
    mapOverItems([&, this](WorldItem *item, int index) {
        items[index % numberOfThreads].push_back(item);
    });
    int threadIndex = 0;
    for (int x = 0; x < numberOfThreads; x++) {
        threads[x] = new sf::Thread([&items, threadIndex, this]() {
            //std::cerr << "starting thread " << threadIndex << std::endl;
            for (auto item: items[threadIndex]) {
                bool canMoveLeft = isItemAtPos(sf::Vector2u(item->getPosition().x - 1, item->getPosition().y)) &&
                                   item->getPosition().x > 0;
                bool canMoveRight = isItemAtPos(sf::Vector2u(item->getPosition().x + 1, item->getPosition().y)) &&
                                    item->getPosition().x < WORLD_SIZE - 1;
                bool canMoveUp = isItemAtPos(sf::Vector2u(item->getPosition().x, item->getPosition().y - 1)) &&
                                 item->getPosition().y > 0;
                bool canMoveDown = isItemAtPos(sf::Vector2u(item->getPosition().x, item->getPosition().y + 1)) &&
                                   item->getPosition().y < WORLD_SIZE - 1;
                item->round(canMoveLeft, canMoveRight, canMoveUp, canMoveDown);
            }
        });
        threads[x]->launch();
        threadIndex++;
    }
    for (auto it: threads) {
        it->wait();
    }
    mapOverItems([&, this](WorldItem *item) {
        auto action = item->getNextAction();
        switch (action) {
            case WorldItemAction::NOOP_MAX_VALUE:
                break;
            case WorldItemAction::MOVE_LEFT: {
                moveItem(item, MOVE_DIRECTION::LEFT);
                break;
            }
            case WorldItemAction::MOVE_RIGHT: {
                moveItem(item, MOVE_DIRECTION::RIGHT);
                break;
            }
            case WorldItemAction::MOVE_UP: {
                moveItem(item, MOVE_DIRECTION::UP);
                break;
            }
            case WorldItemAction::MOVE_DOWN: {
                moveItem(item, MOVE_DIRECTION::DOWN);
                break;
            }
        }
        item->setNextAction(WorldItemAction::NOOP_MAX_VALUE);
    });
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

void World::mapOverItems(const std::function<void(WorldItem *, int)> &fun) {
    int index = 0;
    for (auto &x: items) {
        for (auto &item: x) {
            if (item != nullptr) {
                fun(item, index);
                index++;
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
            if (!isItemAtPos(randomPos)) {
                addItem(new WorldItem(numberOfRoundsPerGeneration), randomPos);
                success = true;
            }
        }
    }
}

bool World::isItemAtPos(sf::Vector2u pos) {
    if (pos.x < 0 || pos.y < 0 || pos.x >= WORLD_SIZE || pos.y >= WORLD_SIZE) {
        return true;
    }
    return items[pos.x][pos.y] != nullptr;
}

void World::depopulate() {
    mapOverItems([&, this](WorldItem *item) {
        deleteItem(item->getPosition());
    });
}

void World::moveItem(WorldItem *item, MOVE_DIRECTION direction) {
    auto pos = item->getPosition();
    auto newPos = pos;
    switch (direction) {
        case MOVE_DIRECTION::LEFT: {
            if (!isItemAtPos(sf::Vector2u(pos.x - 1, pos.y))) {
                newPos = sf::Vector2u(pos.x - 1, pos.y);
            }
            break;
        }
        case MOVE_DIRECTION::RIGHT: {
            if (!isItemAtPos(sf::Vector2u(pos.x + 1, pos.y))) {
                newPos = sf::Vector2u(pos.x + 1, pos.y);
            }
            break;
        }
        case MOVE_DIRECTION::UP: {
            if (!isItemAtPos(sf::Vector2u(pos.x, pos.y - 1))) {
                newPos = sf::Vector2u(pos.x, pos.y - 1);
            }
            break;
        }
        case MOVE_DIRECTION::DOWN: {
            if (!isItemAtPos(sf::Vector2u(pos.x, pos.y + 1))) {
                newPos = sf::Vector2u(pos.x, pos.y + 1);
            }
            break;
        }
    }
    if (newPos.x >= 0 && newPos.y >= 0 && newPos.x < WORLD_SIZE && newPos.y < WORLD_SIZE && (newPos.x != pos.x ||
                                                                                             newPos.y != pos.y)) {
        item->setPosition(newPos);
        items[newPos.x][newPos.y] = items[pos.x][pos.y];
        items[pos.x][pos.y] = nullptr;
    }
}

void World::deleteItem(sf::Vector2u pos) {
    auto item = this->items[pos.x][pos.y];
    delete item;
    this->items[pos.x][pos.y] = nullptr;
}

unsigned int World::getNumberOfPopulation() {
    unsigned int value = 0;
    mapOverItems([&, this](WorldItem *item) {
        value++;
    });
    return value;
}

void World::populateByGenomes(std::vector<std::string> genomes, unsigned int population, float mutationRate) {
    int genomesLength = std::min((int) genomes.size() * 2, (int) population);
    for (auto x = 0; x < genomesLength; x++) {
        auto genome = Genome(genomes[x % genomes.size()]);
        genome.mutateGenome(mutationRate);
        bool success = false;
        while (!success) {
            sf::Vector2u randomPos = sf::Vector2u(getRandomUnsignedInt(0, WORLD_SIZE),
                                                  getRandomUnsignedInt(0, WORLD_SIZE));
            if (!isItemAtPos(randomPos)) {
                addItem(new WorldItem(numberOfRoundsPerGeneration, genome), randomPos);
                success = true;
            }
        }
    }
    auto rest = population - genomesLength;
    populateRandomly(rest);
}
