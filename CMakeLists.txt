cmake_minimum_required(VERSION 3.16)

project(EmbeddedLinuxHealthMonitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(health_monitor
    src/main.cpp
    src/logger.cpp
    src/config_manager.cpp
    src/cpu_monitor.cpp
    src/memory_monitor.cpp
    src/disk_monitor.cpp
    src/temperature_monitor.cpp
    src/network_monitor.cpp
    src/service_monitor.cpp
)

target_include_directories(health_monitor PRIVATE
    include
)

target_compile_options(health_monitor PRIVATE
    -Wall
    -Wextra
)
# Enable testing
enable_testing()

# Configuration test
add_executable(test_config
    tests/test_config.cpp
    src/config_manager.cpp
)
# CPU monitor test
add_executable(test_cpu
    tests/test_cpu.cpp
    src/cpu_monitor.cpp
)

target_include_directories(test_cpu PRIVATE include)

add_test(NAME CpuTest COMMAND test_cpu)

set_tests_properties(CpuTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
target_include_directories(test_config PRIVATE include)
# Memory monitor test
add_executable(test_memory
    tests/test_memory.cpp
    src/memory_monitor.cpp
)

target_include_directories(test_memory PRIVATE include)

add_test(NAME MemoryTest COMMAND test_memory)

set_tests_properties(MemoryTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
# Register the test
add_test(NAME ConfigTest COMMAND test_config)

# Run tests from the build directory
set_tests_properties(ConfigTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
# Service monitor test
add_executable(test_service_monitor
    tests/test_service_monitor.cpp
    src/service_monitor.cpp
)

target_include_directories(test_service_monitor PRIVATE include)

add_test(NAME ServiceMonitorTest COMMAND test_service_monitor)

set_tests_properties(ServiceMonitorTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
# Configuration validation test
add_executable(test_config_validation
    tests/test_config_validation.cpp
    src/config_manager.cpp
)

target_include_directories(test_config_validation PRIVATE include)

add_test(
    NAME ConfigValidationTest
    COMMAND test_config_validation
)

set_tests_properties(ConfigValidationTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
# Disk monitor test
add_executable(test_disk
    tests/test_disk.cpp
    src/disk_monitor.cpp
)

target_include_directories(test_disk PRIVATE include)

add_test(NAME DiskTest COMMAND test_disk)

set_tests_properties(DiskTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
# Network monitor test
add_executable(test_network
    tests/test_network.cpp
    src/network_monitor.cpp
)

target_include_directories(test_network PRIVATE include)

add_test(NAME NetworkTest COMMAND test_network)

set_tests_properties(NetworkTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
# Temperature monitor test
add_executable(test_temperature
    tests/test_temperature.cpp
    src/temperature_monitor.cpp
)

target_include_directories(test_temperature PRIVATE include)

add_test(NAME TemperatureTest COMMAND test_temperature)

set_tests_properties(TemperatureTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
