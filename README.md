# Embedded Linux Device Health Monitor & Auto-Recovery Agent

A C++-based system monitoring tool designed to monitor the health of a Linux device and automatically recover a critical service when it becomes inactive.

## Project Overview

The Embedded Linux Device Health Monitor continuously monitors important system resources, including CPU usage, memory usage, disk usage, temperature, network connectivity, and service status.

When the configured critical service becomes inactive, the monitor tracks consecutive failures and attempts to restart the service after reaching a specified failure threshold.

## Features

- CPU usage monitoring
- Memory usage monitoring
- Disk usage monitoring
- Temperature monitoring through Linux thermal interfaces
- Network interface and connectivity monitoring
- Linux service status monitoring
- Automatic service recovery
- Configurable warning and critical thresholds
- Configurable recovery retry limit
- Timestamped logging
- Systemd service integration
- Unit tests using CTest

## Technologies Used

- C++
- Linux system programming
- CMake
- systemd
- Linux `/proc` and `/sys` interfaces
- nlohmann/json
- CTest
- Linux kernel module (character device driver)

## Project Structure

```text
embedded-linux-health-monitor/
├── config/
│   └── health_monitor.json
├── docs/
│   ├── architecture.md
│   └── test-report.md
├── driver/
├── include/
├── src/
├── scripts/
├── systemd/
├── tests/
├── CMakeLists.txt
├── .gitignore
└── README.md
