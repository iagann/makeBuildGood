#include "BuildMaker.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc > 1) {
        BuildMaker buildMaker;
        if (buildMaker.importFile(argv[1]))
            buildMaker.makeGoodBuild();
        return 0;
    }

    std::cerr << "when running this app please provide a file name with build configuration as an argument" << std::endl;
    return 0;
}