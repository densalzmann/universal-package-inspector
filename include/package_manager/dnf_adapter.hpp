#pragma once
#include "package_manager/package_manager_base.hpp"

class DnfAdapter : public PackageManagerBase {
public:
    ~DnfAdapter() override = default;
protected:
    std::string getCommand() const override {
        return "dnf repoquery --installed --queryformat '%{name} %{version}-%{release}\\n'";
    }

    std::vector<Package> parseOutput(const std::string& output) const override;
};