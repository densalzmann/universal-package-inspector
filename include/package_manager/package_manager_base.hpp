#pragma once
#include <string>
#include <vector>

struct Package {
    std::string name;
    std::string version;
    std::string manager;
};

class PackageManagerBase {
public:
    virtual std::vector<Package> getInstalledPackages() = 0;
    virtual ~PackageManagerBase() = default;
};