#pragma once
#include "package_manager/package_manager_base.hpp"
#include <filesystem>
#include <regex>

class FilesystemScanner {
public:
    std::vector<Package> scan() const {
        std::vector<Package> packages;
        scanDirectory("/usr/local", packages);
        scanDirectory("/opt", packages);
        return packages;
    }

private:
    void scanDirectory(const std::string& directory, std::vector<Package>& packages) const {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_directory() && isPackageDirectory(entry.path())) {
                std::string packageName = entry.path().filename().string();
                std::string packageVersion = extractVersion(entry.path());

                // Check if the package is already handled (i.e., already in the list)
                auto it = std::find_if(packages.begin(), packages.end(), [&](const Package& pkg) {
                    return pkg.name == packageName;
                });

                if (it == packages.end()) {
                    // New package, add it to the list
                    Package pkg = {packageName, packageVersion, "source", {entry.path().string()}};
                    packages.push_back(pkg);
                } else {
                    // Existing package, append the path
                    it->paths.push_back(entry.path().string());
                }
            }
        }
    }

    bool isPackageDirectory(const std::filesystem::path& path) const {
        return std::filesystem::exists(path / "bin") ||
               std::filesystem::exists(path / "lib") ||
               std::filesystem::exists(path / "include") ||
               std::filesystem::exists(path / "share");
    }

    std::string extractVersion(const std::filesystem::path& path) const {
        // A simple regex to extract version from directory names like "package-1.2.3"
        std::regex versionRegex("[-_](\\d+\\.\\d+\\.\\d+)");
        std::smatch match;
        std::string pathStr = path.string();
        if (std::regex_search(pathStr, match, versionRegex)) {
            return match[1];
        }
        return "unknown";  // Return "unknown" if the version cannot be determined
    }
};
