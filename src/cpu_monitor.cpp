#include "cpu_monitor.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

unsigned long long CpuMonitor::readTotalJiffies()
{
    std::ifstream file("/proc/stat");

    std::string line;
    std::getline(file, line);

    std::istringstream stream(line);

    std::string cpu;
    unsigned long long value;
    unsigned long long total = 0;

    stream >> cpu;

    while (stream >> value)
    {
        total += value;
    }

    return total;
}

unsigned long long CpuMonitor::readIdleJiffies()
{
    std::ifstream file("/proc/stat");

    std::string line;
    std::getline(file, line);

    std::istringstream stream(line);

    std::string cpu;
    unsigned long long user, nice, system, idle, iowait = 0;
    unsigned long long irq, softirq, steal;

    stream >> cpu >> user >> nice >> system >> idle
           >> iowait >> irq >> softirq >> steal;

    return idle + iowait;
}

MonitorResult CpuMonitor::check(double warning, double critical)
{
    auto total1 = readTotalJiffies();
    auto idle1 = readIdleJiffies();

    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)
    );

    auto total2 = readTotalJiffies();
    auto idle2 = readIdleJiffies();

    auto totalDifference = total2 - total1;
    auto idleDifference = idle2 - idle1;

    double usage = 0.0;

    if (totalDifference > 0)
    {
        usage = 100.0 *
            (1.0 - static_cast<double>(idleDifference) /
            static_cast<double>(totalDifference));
    }

    MonitorStatus status = MonitorStatus::OK;
    std::string message = "CPU usage normal";

    if (usage >= critical)
    {
        status = MonitorStatus::CRITICAL;
        message = "CPU usage critical";
    }
    else if (usage >= warning)
    {
        status = MonitorStatus::WARNING;
        message = "CPU usage high";
    }

    return {
        "CPU",
        usage,
        status,
        message
    };
}
