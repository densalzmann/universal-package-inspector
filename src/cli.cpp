#include "cli.hpp"
#include "package_manager/apt_adapter.hpp"
#include "package_manager/pip_adapter.hpp"
#include "filesystem_scanner.hpp"
#include "conflict_analyzer.hpp"
#include "report_generator.hpp"

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
        // Initialize components
        AptAdapter apt;
        PipAdapter pip;
        FilesystemScanner fsScanner;
        ConflictAnalyzer analyzer;
        ReportGenerator reporter;
        
        // Perform scanning
        auto aptPackages = apt.getInstalledPackages();
        auto pipPackages = pip.getInstalledPackages();
        auto fsPackages = fsScanner.scan();

        // Analyze for conflicts
        auto conflicts = analyzer.detectConflicts(aptPackages, pipPackages, fsPackages);

        // Generate report
        reporter.generateReport(conflicts, outputFormat);
    }
}