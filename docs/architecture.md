# Embedded Linux Device Health Monitor & Auto-Recovery Agent

## 1. Project Overview

The Embedded Linux Device Health Monitor is a C++ application
that continuously monitors the health of a Linux system.

It monitors CPU usage, memory usage, disk usage, temperature,
network connectivity, and critical system services.

When a monitored service fails repeatedly, the application
attempts automatic recovery by restarting the service.

## 2. System Architecture

The application consists of the following modules:

- Main Controller: Coordinates monitoring and recovery.
- CPU Monitor: Reads CPU statistics from /proc/stat.
- Memory Monitor: Reads RAM statistics from /proc/meminfo.
- Disk Monitor: Checks disk usage using statvfs().
- Temperature Monitor: Reads the Linux thermal sensor.
- Network Monitor: Checks interface status and connectivity.
- Service Monitor: Checks and restarts system services.
- Config Manager: Loads thresholds and settings from JSON.
- Logger: Records monitoring events and errors.

## 3. Monitoring Workflow

1. Load configuration from the JSON file.
2. Initialize all monitoring modules.
3. Collect system health information.
4. Compare readings against configured thresholds.
5. Display and log the results.
6. Check whether a critical service is active.
7. After repeated failures, attempt service recovery.
8. Wait for the configured interval and repeat.

## 4. Automatic Recovery

The service monitor detects inactive services.

The main controller counts consecutive failures.
After three consecutive failures, it attempts to restart
the service.

The application limits recovery attempts and applies a
cooldown period between attempts.

## 5. Configuration

The configuration file is:

config/health_monitor.json

It contains monitoring intervals, warning and critical
thresholds, temperature sensor path, network settings,
and service recovery settings.

## 6. Deployment

The application is compiled using CMake and C++17.

A systemd service allows the monitor to start automatically
and restart if the monitoring application exits unexpectedly.

## 7. Testing

The project includes tests for:

- Configuration loading and validation
- CPU monitoring
- Memory monitoring
- Service status monitoring

Tests are executed using CTest.
