#pragma once
#include "package_manager/package_manager_base.hpp"

class DpkgAdapter : public PackageManagerBase {
public:
    ~DpkgAdapter() override = default;
    // std::vector<Package> getInstalledPackages() override;
protected:
    std::string getCommand() const override {
        return "dpkg-query -W -f='${Package} ${Version}\\n'";
    }

    std::vector<Package> parseOutput(const std::string& output) const override;
};