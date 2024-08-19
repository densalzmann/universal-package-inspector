#pragma once
#include "package_manager/package_manager_base.hpp"

class PipAdapter : public PackageManagerBase {
public:
    ~PipAdapter() override = default;
protected:
    std::string getCommand() const override {
        return "pip list --format=freeze";
    }

    std::vector<Package> parseOutput(const std::string& output) const override;
    // std::vector<Package> getInstalledPackages() override;
};