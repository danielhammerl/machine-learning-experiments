//
// Created by Daniel Hammerl on 01.05.23.
//

#include "Framework.h"
#include "Utils.h"
#include <iostream>
#include <sstream>

Framework::Framework(Experiment *_experiment, int argc, char **argv) : experiment(_experiment) {
    world = new World();

    createDirectoryIfDoesntExist("screenshots");
}

Framework::~Framework() {
    delete world;
}

void Framework::run() {
    while (currentGeneration <= experiment->maxNumberOfGenerations) {
        bool renderThisGeneration = experiment->generationsToRender.find(currentGeneration) !=
                                    experiment->generationsToRender.end();

        startGeneration();

        while (currentRound <= experiment->numberOfRoundsPerGeneration) {
            round();
            if (renderThisGeneration) {
                render();
            }
            currentRound++;
        }

        endGeneration();
        currentRound = 1;
        currentGeneration++;
    }
}

void Framework::startGeneration() {
    std::cout << "start generation " << currentGeneration << std::endl;
    world->populateRandomly(experiment->maxNumberOfBeings);
}

void Framework::endGeneration() {
    std::cout << "end generation " << currentGeneration << std::endl;
    experiment->endGeneration();
    world->depopulate();
}

void Framework::round() {

}

void Framework::render() {
    sf::RenderTexture renderTexture;
    renderTexture.create(WORLD_SIZE, WORLD_SIZE);
    renderTexture.clear(sf::Color::White);

    world->mapOverItems([&](WorldItem *item) {
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(1, 1));
        shape.setPosition((sf::Vector2f) item->getPosition());
        shape.setFillColor(item->getColor());
        renderTexture.draw(shape);
    });

    renderTexture.display();
    std::stringstream filename;
    filename << "screenshots/";
    filename << this->currentGeneration;
    createDirectoryIfDoesntExist(filename.str().c_str());
    filename << "/";
    filename << this->currentRound;
    filename << ".png";
    renderTexture.getTexture().copyToImage().saveToFile(filename.str());
}
