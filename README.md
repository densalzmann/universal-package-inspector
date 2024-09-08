# Universal Package Inspector (UPI) CLI

## Overview

**Universal Package Inspector (UPI)** is an in-progress command-line tool designed to scan and analyze installed packages across multiple package managers on a Linux system. UPI aims to detect potential conflicts, such as duplicate packages, version mismatches, or file path overlaps, and generate detailed reports in various formats, such as text, JSON, or HTML.

The tool currently supports the following package managers:

- `dpkg` (Debian-based systems)
- `rpm` (Red Hat-based systems)
- `dnf`
- `flatpak`
- `snap`
- `pip` (Python packages)

## Features

- **Multi-Package Manager Support**: Simultaneously scans for packages installed by different package managers and analyzes potential conflicts between them.
  
- **Conflict Detection**: Identifies several types of conflicts:
  - **Version Conflicts**: Detects different versions of the same package installed via different managers.
  - **Manager Conflicts**: Flags situations where multiple managers have installed the same package.
  - **File Path Conflicts** (planned): Detects if different packages install files to the same locations.

- **Report Generation**: Outputs conflict reports in multiple formats:
  - **Text**
  - **JSON**
  - **HTML**

## Project Status

This project is currently in progress and has been tested on Fedora. The core functionality for package scanning, conflict detection, and basic report generation is implemented. Further enhancements and additional features are planned.

## Installation

### Prerequisites

- **C++17** or higher
- **CMake** (for building the project)
- **nlohmann/json** (for JSON report generation)

### Building from Source

To build the UPI CLI tool from source:

1. Clone the repository:
    ```bash
    git clone <repository-url>
    cd unified-package-inspector
    ```

2. Create a build directory and compile the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run the CLI tool:
    ```bash
    ./upi_cli
    ```

## Usage

### Command-Line Interface (CLI)

UPI is used through its CLI, allowing you to scan for package conflicts and generate reports.

```bash
./upi_cli scan --output-format <format>
```

## Available Options

- `scan`: Scans the system for installed packages and detects conflicts.
- `--output-format <format>`: Specifies the output format for the report. Options include `text`, `json`, and `html`.

## Example

Generate a conflict report in JSON format:

```bash
./upi_cli scan --output-format json
```

## Configuration

Currently, UPI automatically detects available package managers and scans for packages installed by them. The tool includes related manager pairs, like `dnf` and `rpm`, to avoid false positives for packages that are inherently linked unless there is a version mismatch.

### Adding Related Package Managers

To extend the tool to support additional related package managers, modify the `relatedManagers` map in the `conflict_analyzer.cpp` file.

## Project Structure

- **`cli.cpp`**: Implements the command-line interface, handling user input and orchestrating the scanning and reporting process.
- **`conflict_analyzer.cpp`**: Contains the logic to detect conflicts between packages, such as version mismatches or duplicate installations by different managers.
- **`report_generator.cpp`**: Generates conflict reports in text, JSON, or HTML formats based on the detected issues.
- **Package Manager Adapters**: Each supported package manager has a dedicated adapter:
  - **`dpkg_adapter.cpp`**
  - **`rpm_adapter.cpp`**
  - **`dnf_adapter.cpp`**
  - **`flatpak_adapter.cpp`**
  - **`snap_adapter.cpp`**
  - **`pip_adapter.cpp`**

## Contributing

Contributions to UPI are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`feature/your-feature`).
3. Commit your changes (`git commit -m 'Add your feature'`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Create a Pull Request.

## Development
  
### Dev Dependencies:
    * libgtest-dev for apt / gtest-devel for fedora

### Run:
    * ./build/upi scan text

### ToDo:
    * [x] detect available package managers
    * [x] implement filesystem scanner
    * [x] implement a conflict search for available package managers
    * [x] create a suitable report generator
    * [ ] look what package managers may in real have conflicts and what type of conflicts
    * [ ] create a test docker container with included conflicts for e2e tests
    * [ ] include package managers: ...

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contact

For support or any inquiries, please contact `den.salzmann@gmail.com`.



