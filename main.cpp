#include "src/framework/Framework.h"
#include "src/experiment/00-test/Test.h"
#include "src/framework/Utils.h"
#include "src/framework/engine/NeuronalNetwork.h"


int main(int argc, char *argv[]) {

    Test experiment;

    auto *framework = new Framework(&experiment, argc, argv);

    framework->run();
}
