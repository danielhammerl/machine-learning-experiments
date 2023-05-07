//
// Created by Daniel Hammerl on 01.05.23.
//

#include "WorldItem.h"

WorldItem::WorldItem() {
}

WorldItem::~WorldItem() {
}

/*
void WorldItem::move(int x, int y) {
    sf::Vector2f newPos = sf::Vector2f(shape->getPosition().x + (float) x * WORLD_ITEM_SIZE,
                                       shape->getPosition().y + (float) y * WORLD_ITEM_SIZE);

    std::cout << newPos.x << "-" << newPos.y << std::endl;

    newPos.x = newPos.x < 0 ? 0 : newPos.x;
    newPos.y = newPos.y < 0 ? 0 : newPos.y;
    newPos.x = newPos.x > WORLD_SIZE - WORLD_ITEM_SIZE ? WORLD_SIZE - WORLD_ITEM_SIZE : newPos.x;
    newPos.y = newPos.y > WORLD_SIZE - WORLD_ITEM_SIZE ? WORLD_SIZE - WORLD_ITEM_SIZE : newPos.y;
    shape->setPosition(newPos);
}*/

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
