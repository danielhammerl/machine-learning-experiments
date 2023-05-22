//
// Created by Daniel Hammerl on 01.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_WORLDITEM_H
#define MACHINELEARNINGEXPERIMENTS_WORLDITEM_H

#include <string>
#include <SFML/Graphics.hpp>
#include "../../Utils.h"
#include "../NeuronalNetwork.h"

class WorldItem {
public:
    WorldItem();

    ~WorldItem();

    void setPosition(sf::Vector2u pos);

    sf::Vector2u getPosition();

    void round();

    sf::Color getColor();

    enum class WorldItemSensor {
        RANDOM,
        NOOP_MAX_VALUE,
    };

    enum class WorldItemAction {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT_UP,
        MOVE_RIGHT_UP,
        MOVE_LEFT_DOWN,
        MOVE_RIGHT_DOWN,
        NOOP_MAX_VALUE,
    };

    void setNextAction(WorldItemAction action) {
        nextAction = action;
    }

    [[nodiscard]] WorldItemAction getNextAction() const {
        return this->nextAction;
    }

    std::vector<double> getSensorData();

protected:
    void move(MOVE_DIRECTION direction);

private:
    WorldItemAction nextAction = WorldItemAction::NOOP_MAX_VALUE;
    sf::Vector2u position;

    NeuronalNetwork *brain;
};


#endif //MACHINELEARNINGEXPERIMENTS_WORLDITEM_H
