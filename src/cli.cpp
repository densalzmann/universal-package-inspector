#include "cli.hpp"
#include "package_manager/dpkg_adapter.hpp"
#include "package_manager/rpm_adapter.hpp"
#include "package_manager/dnf_adapter.hpp"
#include "package_manager/flatpak_adapter.hpp"
#include "package_manager/snap_adapter.hpp"
#include "package_manager/pip_adapter.hpp"
#include "filesystem_scanner.hpp"
#include "conflict_analyzer.hpp"
#include "report_generator.hpp"
#include <memory>
#include <vector>

void CLI::parseArguments(int argc, char* argv[]) {
    // Simple argument parsing for demonstration purposes
    // In a full implementation, use a proper argument parsing library
    if (argc > 1) {
        command = argv[1];
        if (argc > 2) {
            outputFormat = argv[2];
        }
    }
}

void CLI::execute() {
    if (command == "scan") {
        // Create a vector to hold dynamically allocated adapters
        std::vector<std::unique_ptr<PackageManagerBase>> availableAdapters;

        // Initialize components
        std::unique_ptr<DpkgAdapter> dpkg = std::make_unique<DpkgAdapter>();
        std::unique_ptr<RpmAdapter> rpm = std::make_unique<RpmAdapter>();
        std::unique_ptr<DnfAdapter> dnf = std::make_unique<DnfAdapter>();
        std::unique_ptr<FlatpakAdapter> flatpak = std::make_unique<FlatpakAdapter>();
        std::unique_ptr<SnapAdapter> snap = std::make_unique<SnapAdapter>();
        std::unique_ptr<PipAdapter> pip = std::make_unique<PipAdapter>();

        // Check availability and add to vector if available
        if (dpkg->isAvailable()) availableAdapters.push_back(std::move(dpkg));
        if (rpm->isAvailable()) availableAdapters.push_back(std::move(rpm));
        if (dnf->isAvailable()) availableAdapters.push_back(std::move(dnf));
        if (flatpak->isAvailable()) availableAdapters.push_back(std::move(flatpak));
        if (snap->isAvailable()) availableAdapters.push_back(std::move(snap));
        if (pip->isAvailable()) availableAdapters.push_back(std::move(pip));

        FilesystemScanner fsScanner;
        ConflictAnalyzer analyzer;
        ReportGenerator reporter;

        std::vector<Package> allPackages;

        // Perform scanning using available adapters
        for (const auto& adapter : availableAdapters) {
            auto packages = adapter->getInstalledPackages();
            // Debug string
            for (auto package: packages) {
                std::cout << package;
            }
            allPackages.insert(allPackages.end(), packages.begin(), packages.end());
        }

        auto fsPackages = fsScanner.scan();
        allPackages.insert(allPackages.end(), fsPackages.begin(), fsPackages.end());

        // Analyze for conflicts
        auto conflicts = analyzer.detectConflicts(allPackages);

        // Generate report
        reporter.generateReport(conflicts, outputFormat);
    }
}