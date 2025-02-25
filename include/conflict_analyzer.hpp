#pragma once
#include <vector>
#include "package_manager/package_manager_base.hpp"

struct Conflict {
    std::string packageName;
    std::string issue;
    std::vector<Package> involvedPackages;
};

class ConflictAnalyzer {
public:
    std::vector<Conflict> detectConflicts(std::vector<Package>);
};