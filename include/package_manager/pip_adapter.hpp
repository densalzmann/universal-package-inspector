#pragma once
#include "package_manager/package_manager_base.hpp"

class PipAdapter : public PackageManagerBase {
public:
    ~PipAdapter() override = default;
    std::vector<Package> getInstalledPackages() override;
};