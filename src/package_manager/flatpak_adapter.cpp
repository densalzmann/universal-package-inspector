#include "package_manager/flatpak_adapter.hpp"
#include <iostream>
#include <sstream>

std::vector<Package> FlatpakAdapter::parseOutput(const std::string& output) const {
    std::vector<Package> packages;
    std::istringstream iss(output);
    std::string line;

    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string appName, appVersion;
        lineStream >> appName >> appVersion;

        packages.push_back({appName, appVersion, "flatpak"});
    }

    return packages;
}