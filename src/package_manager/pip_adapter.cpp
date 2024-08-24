#include "package_manager/pip_adapter.hpp"
#include <iostream>
#include <sstream> 

std::vector<Package> PipAdapter::parseOutput(const std::string& output) const {
    std::vector<Package> packages;
    std::istringstream iss(output);
    std::string line;

    while (std::getline(iss, line)) {
        size_t equalSignPos = line.find("==");
        if (equalSignPos != std::string::npos) {
            std::string packageName = line.substr(0, equalSignPos);
            std::string packageVersion = line.substr(equalSignPos + 2);

            packages.push_back({packageName, packageVersion, "pip"});
        }
    }
    return packages;
}