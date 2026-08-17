#include "RunManager.hh"

int main(int argc, char** argv) {
    auto runManager = RunManager(argc, argv);
    runManager.run();
    return 0;
}
