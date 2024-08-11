#pragma once
#include <string>
#include <vector>
#include "package_manager/package_manager_base.hpp"

class FilesystemScanner {
public:
    std::vector<Package> scan();
};
