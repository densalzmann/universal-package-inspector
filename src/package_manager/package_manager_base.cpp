#include "package_manager/package_manager_base.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <memory>
#include <sstream>

std::ostream& operator<<(std::ostream &out, Package const &cur_package) {
  out << cur_package.manager << ": " << cur_package.name << " == " << cur_package.version << "\n";
  return out;
}

std::string PackageManagerBase::executeCommand(const std::string& command) const {
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}