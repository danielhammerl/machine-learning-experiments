#include "src/framework/Framework.h"
#include "src/experiment/00-test/Test.h"

int main(int argc, char *argv[]) {

    Test experiment;

    auto *framework = new Framework(&experiment, argc, argv);

    framework->run();
}
