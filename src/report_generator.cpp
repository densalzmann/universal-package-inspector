#include "report_generator.hpp"
#include <iostream>

void ReportGenerator::generateReport(const std::vector<Conflict>& conflicts, const std::string& format) {
    // Example: Simple console output, extend for JSON/HTML output
    if (format == "text") {
        std::cout << "UPI!!! Your report is ready!\n";
        for (const auto& conflict : conflicts) {
            std::cout << "Conflict detected: " << conflict.packageName << "\n";
            for (const auto& pkg : conflict.involvedPackages) {
                std::cout << " - " << pkg.name << " (" << pkg.version << ") from " << pkg.manager << "\n";
            }
        }
    } else if (format == "json") {
        // Implement JSON output
    } else if (format == "html") {
        // Implement HTML output
    }
}