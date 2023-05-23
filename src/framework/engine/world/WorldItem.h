//
// Created by Daniel Hammerl on 01.05.23.
//

#ifndef MACHINELEARNINGEXPERIMENTS_WORLDITEM_H
#define MACHINELEARNINGEXPERIMENTS_WORLDITEM_H

#include <string>
#include <SFML/Graphics.hpp>
#include "../../Utils.h"
#include "../NeuronalNetwork.h"
#include "Genome.h"

enum class WorldItemSensor {
    RANDOM,
    X_POS,
    Y_POS,
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

static NEURON_COUNT_TYPE NUMBER_OF_INPUT_NEURONS = static_cast<NEURON_COUNT_TYPE>(WorldItemSensor::NOOP_MAX_VALUE);
static NEURON_COUNT_TYPE NUMBER_OF_OUTPUT_NEURONS = static_cast<NEURON_COUNT_TYPE>(WorldItemAction::NOOP_MAX_VALUE);

class WorldItem {
public:
    WorldItem();
    WorldItem(Genome genome);

    ~WorldItem();

    void setPosition(sf::Vector2u pos);

    sf::Vector2u getPosition();

    void round();

    sf::Color getColor();

    void setNextAction(WorldItemAction action) {
        nextAction = action;
    }

    [[nodiscard]] WorldItemAction getNextAction() const {
        return this->nextAction;
    }

    std::vector<double> getSensorData();

    std::string getGenomeAsString();

protected:
    void move(MOVE_DIRECTION direction);

private:
    WorldItemAction nextAction = WorldItemAction::NOOP_MAX_VALUE;
    sf::Vector2u position;

    NeuronalNetwork *brain;
};


#endif //MACHINELEARNINGEXPERIMENTS_WORLDITEM_H
