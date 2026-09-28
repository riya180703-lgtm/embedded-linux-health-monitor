#include "disk_monitor.h"

#include <sys/statvfs.h>

MonitorResult DiskMonitor::check(
    double warning,
    double critical)
{
    struct statvfs diskInfo{};

    if (statvfs("/", &diskInfo) != 0)
    {
        return {
            "Disk",
            0.0,
            MonitorStatus::CRITICAL,
            "Unable to read disk information"
        };
    }

    unsigned long long total =
        static_cast<unsigned long long>(diskInfo.f_blocks) *
        diskInfo.f_frsize;

    unsigned long long available =
        static_cast<unsigned long long>(diskInfo.f_bavail) *
        diskInfo.f_frsize;

    if (total == 0 || available > total)
    {
        return {
            "Disk",
            0.0,
            MonitorStatus::CRITICAL,
            "Invalid disk information"
        };
    }

    unsigned long long used = total - available;

    double usage =
        100.0 * static_cast<double>(used) /
        static_cast<double>(total);

    MonitorStatus status = MonitorStatus::OK;
    std::string message = "Disk usage normal";

    if (usage >= critical)
    {
        status = MonitorStatus::CRITICAL;
        message = "Disk usage critical";
    }
    else if (usage >= warning)
    {
        status = MonitorStatus::WARNING;
        message = "Disk usage high";
    }

    return {
        "Disk",
        usage,
        status,
        message
    };
}
