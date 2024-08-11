#pragma once
#include <string>

class CLI {
public:
    void parseArguments(int argc, char* argv[]);
    void execute();
    
private:
    std::string command;
    std::string outputFormat;
};