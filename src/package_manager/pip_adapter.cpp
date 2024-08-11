#include "package_manager/pip_adapter.hpp"
#include <iostream>

std::vector<Package> PipAdapter::getInstalledPackages() {
    std::vector<Package> packages;
    // Example: Mocked data for simplicity, replace with actual `dpkg` command parsing
    packages.push_back({"libc6", "2.31-0ubuntu9.9", "pip"});
    packages.push_back({"libstdc++6", "10.3.0-1ubuntu1~20.04", "pip"});
    return packages;
}