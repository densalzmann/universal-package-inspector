#pragma once
#include "package_manager/package_manager_base.hpp"

class AptAdapter : public PackageManagerBase {
public:
    ~AptAdapter() override = default;
    std::vector<Package> getInstalledPackages() override;
};