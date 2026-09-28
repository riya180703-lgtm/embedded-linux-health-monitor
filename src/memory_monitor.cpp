#include "memory_monitor.h"

#include <fstream>
#include <string>

MonitorResult MemoryMonitor::check(
    double warning,
    double critical)
{
    std::ifstream file("/proc/meminfo");

    if (!file)
    {
        return {
            "Memory", 0.0,
            MonitorStatus::CRITICAL,
            "Unable to read /proc/meminfo"
        };
    }

    std::string key;
    unsigned long long value;
    std::string unit;

    unsigned long long memTotal = 0;
    unsigned long long memAvailable = 0;

    while (file >> key >> value >> unit)
    {
        if (key == "MemTotal:")
            memTotal = value;

        else if (key == "MemAvailable:")
            memAvailable = value;
    }

    if (memTotal == 0 || memAvailable > memTotal)
    {
        return {
            "Memory", 0.0,
            MonitorStatus::CRITICAL,
            "Invalid memory information"
        };
    }

    double usage =
        100.0 * (memTotal - memAvailable) / memTotal;

    MonitorStatus status = MonitorStatus::OK;
    std::string message = "Memory usage normal";

    if (usage >= critical)
    {
        status = MonitorStatus::CRITICAL;
        message = "Memory usage critical";
    }
    else if (usage >= warning)
    {
        status = MonitorStatus::WARNING;
        message = "Memory usage high";
    }

    return {
        "Memory",
        usage,
        status,
        message
    };
}
