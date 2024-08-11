#include "package_manager/apt_adapter.hpp"
#include <iostream>

std::vector<Package> AptAdapter::getInstalledPackages() {
    std::vector<Package> packages;
    // Example: Mocked data for simplicity, replace with actual `dpkg` command parsing
    packages.push_back({"libc6", "2.31-0ubuntu9.9", "apt"});
    packages.push_back({"libstdc++6", "10.3.0-1ubuntu1~20.04", "apt"});
    std::cout << "Following packages find in apt:\n";
    for (const auto& package : packages) {
        std::cout << "\t" << package.name << " == " << package.version << "\n";
    }
    return packages;
}