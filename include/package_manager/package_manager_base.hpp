#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Package {
    std::string name;
    std::string version;
    std::string manager;
    friend std::ostream& operator<<(std::ostream &out, Package const &cur_package);
};

class PackageManagerBase {
public:
    // virtual std::vector<Package> getInstalledPackages() = 0;
    virtual ~PackageManagerBase() = default;
    std::vector<Package> getInstalledPackages() {
        std::string command = getCommand();
        std::string result = executeCommand(command);
        return parseOutput(result);
    }
    // Common method to check if the package manager is available
    bool isAvailable() const {
        std::string command = "command -v " + getCommandName() + " > /dev/null 2>&1";
        if (std::system(command.c_str()) == 0) std::cout << "Found " << getCommandName() << " package manager.\n";
        else std::cout << "The " << getCommandName() << " package manager could not be found.\n";
        return std::system(command.c_str()) == 0;
    }

protected:
    // Each adapter will provide the name of its command (e.g., dpkg-query, rpm)
    virtual std::string getCommandName() const = 0;

    // Method to return the specific command for each adapter
    virtual std::string getCommand() const = 0;

    // Method to parse the command output
    virtual std::vector<Package> parseOutput(const std::string& output) const = 0;

private:
    // Helper method to execute a command and return its output
    std::string executeCommand(const std::string& command) const;
};