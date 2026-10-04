# Embedded Linux Device Health Monitor & Auto-Recovery Agent

A C++-based system monitoring tool designed to monitor the health of a Linux device and automatically recover a critical service when it becomes inactive.

## Project Overview

The Embedded Linux Device Health Monitor continuously monitors important system resources, including CPU usage, memory usage, disk usage, temperature, network connectivity, and Linux service status.

When the configured critical service becomes inactive, the monitor tracks consecutive failures and attempts to restart the service after reaching a specified failure threshold.

The project also includes a Linux character device driver that demonstrates kernel-space and user-space interaction through a device file.

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
- Linux character device driver
- User-space and kernel-space interaction
- Unit tests using CTest

## Technologies Used

- C++
- Linux system programming
- Linux kernel modules
- Linux character device driver
- CMake
- systemd
- Linux `/proc` and `/sys` interfaces
- Linux `/dev` device interface
- nlohmann/json
- CTest

## Project Structure

```text
embedded-linux-health-monitor/
├── config/
│   └── health_monitor.json
├── docs/
│   ├── architecture.md
│   └── test-report.md
├── driver/
│   ├── Makefile
│   └── health_monitor_driver.c
├── include/
│   ├── config_manager.h
│   ├── cpu_monitor.h
│   ├── disk_monitor.h
│   ├── driver_interface.h
│   ├── logger.h
│   ├── memory_monitor.h
│   ├── monitor_result.h
│   ├── network_monitor.h
│   ├── service_monitor.h
│   └── temperature_monitor.h
├── src/
│   ├── config_manager.cpp
│   ├── cpu_monitor.cpp
│   ├── disk_monitor.cpp
│   ├── driver_interface.cpp
│   ├── logger.cpp
│   ├── main.cpp
│   ├── memory_monitor.cpp
│   ├── network_monitor.cpp
│   ├── service_monitor.cpp
│   └── temperature_monitor.cpp
├── scripts/
├── systemd/
├── tests/
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## System Architecture

The project follows a modular Linux system-monitoring architecture.

```text
                    Linux System
                         │
        ┌────────────────┼────────────────┐
        │                │                │
       CPU            Memory            Disk
        │                │                │
        └────────────────┼────────────────┘
                         │
                  Health Monitor
                    Application
                         │
          ┌──────────────┼──────────────┐
          │              │              │
      Network        Services      Driver Interface
          │              │              │
          │              │       /dev/health_monitor
          │              │              │
          │              │       Linux Kernel Driver
          │              │              │
          └──────────────┼──────────────┘
                         │
                    Logger / Output
                         │
                  Service Recovery
                         │
                      systemd
```

## Linux Character Device Driver

The project includes a Linux kernel character device driver to demonstrate
Linux device-driver concepts and kernel-space/user-space interaction.

The driver creates the following device:

```text
/dev/health_monitor
```

The C++ health monitor communicates with the driver through the device file
using the standard `open()` and `read()` system calls.

The driver returns a health status message together with system uptime.

### Driver Workflow

1. Build the kernel module using the Linux kernel build system.
2. Load the module using `insmod`.
3. Linux creates `/dev/health_monitor`.
4. The C++ application opens the device.
5. The application reads the driver status.
6. The driver returns health information.
7. The application logs the result.

## Building the Project

### Build the Linux Driver

```bash
cd driver
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
```

Load the driver:

```bash
sudo insmod health_monitor_driver.ko
```

Verify the device:

```bash
ls -l /dev/health_monitor
```

Test the driver:

```bash
cat /dev/health_monitor
```

Example output:

```text
health_monitor: ok, uptime_sec=12345
```

Unload the driver:

```bash
sudo rmmod health_monitor_driver
```

### Build the Health Monitor

From the project root:

```bash
mkdir -p build
cd build
cmake ..
make
```

The application executable is:

```text
build/health_monitor
```

Run the application from the `build` directory:

```bash
./health_monitor ../config/health_monitor.json
```

## Systemd Integration

A systemd unit file is provided in the `systemd/` directory to run the
health monitor as a Linux system service.

The service can be managed using:

```bash
sudo systemctl start device-health-monitor
sudo systemctl stop device-health-monitor
sudo systemctl status device-health-monitor
```

Logs can be viewed using:

```bash
sudo journalctl -u device-health-monitor
```

The application supports automatic recovery of the configured critical
service when consecutive failures reach the configured threshold.

## Testing

The project includes automated unit tests using CTest.

The test suite covers:

- CPU monitoring
- Memory monitoring
- Disk monitoring
- Network monitoring
- Temperature monitoring
- Configuration validation
- Service monitoring

All 8/8 project tests passed successfully during validation.

The Linux character device driver was tested separately by loading the
kernel module and reading from `/dev/health_monitor`.

## Linux Concepts Demonstrated

- Linux kernel modules
- Character device drivers
- `/dev` device files
- Kernel-space and user-space interaction
- `open()` and `read()` system calls
- `/proc` interfaces
- `/sys` interfaces
- `insmod` and `rmmod`
- systemd services
- Automatic service recovery
- CMake-based compilation
- Unit testing with CTest

## Environment

The project was developed and tested in an Ubuntu Linux environment running
inside a VirtualBox virtual machine.

The development environment uses:

- Ubuntu 24.04
- Linux kernel 7.0.0-38-generic
- GCC / G++
- CMake
- GNU Make

## Limitations

The project was tested inside a VirtualBox Ubuntu environment.

The virtual machine does not expose a standard Linux thermal zone such as
`thermal_zone0`. Therefore, the temperature monitor reports that the
temperature sensor is unavailable instead of generating a fake temperature
value.

## Future Enhancements

- Support for physical hardware temperature sensors
- Additional driver interfaces using `ioctl`
- Additional device-health information exposed through the driver
- Hardware-specific monitoring
- Additional automatic recovery policies
- Extended driver functionality
