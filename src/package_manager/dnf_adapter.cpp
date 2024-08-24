#include "package_manager/dnf_adapter.hpp"
#include <iostream>
#include <sstream> 

std::vector<Package> DnfAdapter::parseOutput(const std::string& output) const {
    std::vector<Package> packages;
    std::istringstream iss(output);
    std::string line;

    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string packageName, packageVersion;
        lineStream >> packageName >> packageVersion;

        packages.push_back({packageName, packageVersion, "dnf"});
    }

    return packages;
}