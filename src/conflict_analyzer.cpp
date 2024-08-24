#include "conflict_analyzer.hpp"
#include <map>
#include <set>
#include <iostream>

std::vector<Conflict> ConflictAnalyzer::detectConflicts(std::vector<Package> allPackages) {
    std::vector<Conflict> conflicts;
    std::map<std::string, std::vector<Package>> packageMap;

    // Organize packages by name
    for (const auto& pkg : allPackages) {
        packageMap[pkg.name].push_back(pkg);
    }

    // Define related package managers (dnf and rpm in this example)
    std::map<std::string, std::string> relatedManagers = {
        {"dnf", "rpm"},
        {"rpm", "dnf"},
        // Add other related manager pairs here
    };

    // Detect conflicts
    for (const auto& entry : packageMap) {
        const auto& packages = entry.second;

        if (packages.size() > 1) {
            std::set<std::string> versions;
            std::set<std::string> managers;
            std::set<std::string> paths;

            for (const auto& pkg : packages) {
                versions.insert(pkg.version);
                managers.insert(pkg.manager);
                paths.insert(pkg.paths.begin(), pkg.paths.end());
            }

            // Check if there are multiple versions of the same package
            if (versions.size() > 1) {
                Conflict conflict;
                conflict.packageName = entry.first;
                conflict.issue = "Version conflict";
                conflict.involvedPackages = packages;
                conflicts.push_back(conflict);
            }

            // Check if multiple managers installed the same package, accounting for related managers
            if (managers.size() > 1) {
                bool isRelatedConflict = false;
                for (const auto& mgr1 : managers) {
                    for (const auto& mgr2 : managers) {
                        if (mgr1 != mgr2 && relatedManagers[mgr1] == mgr2) {
                            if (versions.size() > 1) {
                                isRelatedConflict = true;
                            }
                        } else if (mgr1 != mgr2) {
                            isRelatedConflict = true;
                        }
                    }
                }

                if (isRelatedConflict) {
                    Conflict conflict;
                    conflict.packageName = entry.first;
                    conflict.issue = "Multiple package managers installed the same package";
                    conflict.involvedPackages = packages;
                    conflicts.push_back(conflict);
                }
            }

            // // Check for file path conflicts (assume the package struct contains paths)
            // if (paths.size() < packages.size()) {
            //     Conflict conflict;
            //     conflict.packageName = entry.first;
            //     conflict.issue = "File path conflict";
            //     conflict.involvedPackages = packages;
            //     conflicts.push_back(conflict);
            // }
        }
    }

    return conflicts;
}
