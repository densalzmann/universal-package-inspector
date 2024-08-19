#pragma once
#include "package_manager/package_manager_base.hpp"

class SnapAdapter : public PackageManagerBase {
public:
    ~SnapAdapter() override = default;
protected:
    std::string getCommand() const override {
        return "snap list --all";
    }

    std::vector<Package> parseOutput(const std::string& output) const override;
};