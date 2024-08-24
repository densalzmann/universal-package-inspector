#include "package_manager/snap_adapter.hpp"
#include <iostream>
#include <sstream>

std::vector<Package> SnapAdapter::parseOutput(const std::string& output) const {
    std::vector<Package> packages;
    std::istringstream iss(output);
    std::string line;

    // Skip the header line
    std::getline(iss, line);

    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string packageName, packageVersion, extra;
        lineStream >> packageName >> packageVersion >> extra;

        packages.push_back({packageName, packageVersion, "snap"});
    }
    
    return packages;
}