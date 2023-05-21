//
// Created by Daniel Hammerl on 01.05.23.
//

#include "World.h"
#include <iostream>

World::World() {

}

World::~World() {

}

void World::round() {
    mapOverItems([&, this](WorldItem *item) {
        item->round();
    });
    mapOverItems([&, this](WorldItem *item) {
        auto action = item->getNextAction();
        switch (action) {
            case WorldItem::WorldItemAction::NONE:
                break;
            case WorldItem::WorldItemAction::MOVE_RIGHT_DOWN: {
                moveItem(item, MOVE_DIRECTION::DOWN_RIGHT);
                break;
            }
            case WorldItem::WorldItemAction::MOVE_RIGHT_UP: {
                moveItem(item, MOVE_DIRECTION::UP_RIGHT);
                break;
            }
            case WorldItem::WorldItemAction::MOVE_LEFT_DOWN: {
                moveItem(item, MOVE_DIRECTION::DOWN_LEFT);
                break;
            }
            case WorldItem::WorldItemAction::MOVE_LEFT_UP: {
                moveItem(item, MOVE_DIRECTION::UP_LEFT);
                break;
            }
            case WorldItem::WorldItemAction::MOVE_LEFT: {
                moveItem(item, MOVE_DIRECTION::LEFT);
                break;
            }
            case WorldItem::WorldItemAction::MOVE_RIGHT: {
                moveItem(item, MOVE_DIRECTION::RIGHT);
                break;
            }
            case WorldItem::WorldItemAction::MOVE_UP: {
                moveItem(item, MOVE_DIRECTION::UP);
                break;
            }
            case WorldItem::WorldItemAction::MOVE_DOWN: {
                moveItem(item, MOVE_DIRECTION::DOWN);
                break;
            }
        }
        item->setNextAction(WorldItem::WorldItemAction::NONE);
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
    if (pos.x < 0 || pos.y < 0 || pos.x >= WORLD_SIZE || pos.y >= WORLD_SIZE) {
        return true;
    }
    return items[pos.x][pos.y] != nullptr;
}

void World::depopulate() {
    mapOverItems([&, this](WorldItem *item) {
        this->items[item->getPosition().x][item->getPosition().y] = nullptr;
        delete item;
    });
}

void World::moveItem(WorldItem *item, MOVE_DIRECTION direction) {
    auto pos = item->getPosition();
    auto newPos = pos;
    switch (direction) {
        case MOVE_DIRECTION::DOWN_RIGHT: {
            if (!isItemAtPos(sf::Vector2u(pos.x + 1, pos.y + 1))) {
                newPos = sf::Vector2u(pos.x + 1, pos.y + 1);
            }
            break;
        }
        case MOVE_DIRECTION::UP_RIGHT: {
            if (!isItemAtPos(sf::Vector2u(pos.x + 1, pos.y - 1))) {
                newPos = sf::Vector2u(pos.x + 1, pos.y - 1);
            }
            break;
        }
        case MOVE_DIRECTION::DOWN_LEFT: {
            if (!isItemAtPos(sf::Vector2u(pos.x - 1, pos.y + 1))) {
                newPos = sf::Vector2u(pos.x - 1, pos.y + 1);
            }
            break;
        }
        case MOVE_DIRECTION::UP_LEFT: {
            if (!isItemAtPos(sf::Vector2u(pos.x - 1, pos.y - 1))) {
                newPos = sf::Vector2u(pos.x - 1, pos.y - 1);
            }
            break;
        }
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
