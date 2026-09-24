cmake_minimum_required(VERSION 3.16)

project(EmbeddedLinuxHealthMonitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(health_monitor
    src/main.cpp
    src/logger.cpp
    src/config_manager.cpp
)

target_include_directories(health_monitor PRIVATE
    include
)

target_compile_options(health_monitor PRIVATE
    -Wall
    -Wextra
)
