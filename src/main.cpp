#include "cli.hpp"

int main(int argc, char* argv[]) {
    CLI cli;
    cli.parseArguments(argc, argv);
    cli.execute();
    return 0;
}
