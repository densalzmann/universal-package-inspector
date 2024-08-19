#pragma once
#include "package_manager/package_manager_base.hpp"

class FlatpakAdapter : public PackageManagerBase {
public:
    ~FlatpakAdapter() override = default;
protected:
    std::string getCommand() const override {
        return "flatpak list --columns=application,version";
    }

    std::vector<Package> parseOutput(const std::string& output) const override;
};