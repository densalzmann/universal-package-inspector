#pragma once
#include <string>
#include <vector>
#include "conflict_analyzer.hpp"

class ReportGenerator {
public:
    void generateReport(const std::vector<Conflict>& conflicts, const std::string& format);
};