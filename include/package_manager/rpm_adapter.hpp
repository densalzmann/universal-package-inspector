#pragma once
#include "package_manager/package_manager_base.hpp"

class RpmAdapter : public PackageManagerBase {
public:
    ~RpmAdapter() override = default;
protected:
    std::string getCommandName() const override {
            return "rpm";
        }
    std::string getCommand() const override {
        return "rpm -qa --queryformat '%{NAME} %{VERSION}-%{RELEASE}\\n'";
    }

    std::vector<Package> parseOutput(const std::string& output) const override;
};