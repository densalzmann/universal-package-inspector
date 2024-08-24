// #include "report_generator.hpp"
// #include <iostream>

// void ReportGenerator::generateReport(const std::vector<Conflict>& conflicts, const std::string& format) {
//     // Example: Simple console output, extend for JSON/HTML output
//     if (format == "text") {
//         std::cout << "UPI!!! Your report is ready!\n";
//         for (const auto& conflict : conflicts) {
//             std::cout << "Conflict detected: " << conflict.packageName << "\n";
//             for (const auto& pkg : conflict.involvedPackages) {
//                 std::cout << " - " << pkg.name << " (" << pkg.version << ") from " << pkg.manager << "\n";
//             }
//         }
//     } else if (format == "json") {
//         // Implement JSON output
//     } else if (format == "html") {
//         // Implement HTML output
//     }
// }

#include "report_generator.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void ReportGenerator::generateReport(const std::vector<Conflict>& conflicts, const std::string& format) {
    if (format == "text") {
        std::cout << "UPI!!! Your report is ready!\n";
        for (const auto& conflict : conflicts) {
            std::cout << "Conflict detected: " << conflict.packageName << "\n";
            std::cout << "Issue: " << conflict.issue << "\n";
            for (const auto& pkg : conflict.involvedPackages) {
                std::cout << " - " << pkg.name << " (" << pkg.version << ") from " << pkg.manager << "\n";
                for (const auto& path : pkg.paths) {
                    std::cout << "   Path: " << path << "\n";
                }
            }
            std::cout << "Recommendation: " << getRecommendation(conflict) << "\n";
            std::cout << "\n";
        }
    } else if (format == "json") {
        json reportJson;
        for (const auto& conflict : conflicts) {
            json conflictJson;
            conflictJson["package"] = conflict.packageName;
            conflictJson["issue"] = conflict.issue;

            for (const auto& pkg : conflict.involvedPackages) {
                json packageJson;
                packageJson["name"] = pkg.name;
                packageJson["version"] = pkg.version;
                packageJson["manager"] = pkg.manager;
                packageJson["paths"] = pkg.paths;
                conflictJson["packages"].push_back(packageJson);
            }

            conflictJson["recommendation"] = getRecommendation(conflict);
            reportJson["conflicts"].push_back(conflictJson);
        }

        std::ofstream jsonFile("conflict_report.json");
        jsonFile << reportJson.dump(4); // Pretty-print with an indent of 4 spaces
        jsonFile.close();
    } else if (format == "html") {
        std::ofstream htmlFile("conflict_report.html");
        htmlFile << "<html><head><title>Package Conflict Report</title></head><body>\n";
        htmlFile << "<h1>UPI!!! Your report is ready!</h1>\n";

        for (const auto& conflict : conflicts) {
            htmlFile << "<h2>Conflict detected: " << conflict.packageName << "</h2>\n";
            htmlFile << "<p>Issue: " << conflict.issue << "</p>\n";
            htmlFile << "<ul>\n";
            for (const auto& pkg : conflict.involvedPackages) {
                htmlFile << "<li>" << pkg.name << " (" << pkg.version << ") from " << pkg.manager << "\n";
                htmlFile << "<ul>\n";
                for (const auto& path : pkg.paths) {
                    htmlFile << "<li>Path: " << path << "</li>\n";
                }
                htmlFile << "</ul>\n";
                htmlFile << "</li>\n";
            }
            htmlFile << "</ul>\n";
            htmlFile << "<p><strong>Recommendation:</strong> " << getRecommendation(conflict) << "</p>\n";
        }

        htmlFile << "</body></html>\n";
        htmlFile.close();
    } else {
        std::cerr << "Unsupported format: " << format << "\n";
    }
}

std::string ReportGenerator::getRecommendation(const Conflict& conflict) const {
    if (conflict.issue == "Version conflict") {
        return "Consider aligning package versions or removing one.";
    } else if (conflict.issue == "Multiple package managers installed the same package") {
        return "Decide on a single package manager to maintain the package.";
    } else if (conflict.issue == "File path conflict") {
        return "Check if the file paths overlap or result in unintended overwrites.";
    }
    return "No recommendation available.";
}
