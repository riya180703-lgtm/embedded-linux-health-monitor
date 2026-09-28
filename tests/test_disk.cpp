#include "disk_monitor.h"
#include "monitor_result.h"

#include <cassert>
#include <iostream>

int main()
{
    DiskMonitor diskMonitor;

    MonitorResult result = diskMonitor.check(80, 90);

    // Verify the monitor name
    assert(result.name == "Disk");

    // Disk usage must be between 0 and 100 percent
    assert(result.value >= 0.0);
    assert(result.value <= 100.0);

    // Verify that the monitor returned a valid status
    assert(result.status == MonitorStatus::OK ||
           result.status == MonitorStatus::WARNING ||
           result.status == MonitorStatus::CRITICAL);

    std::cout << "Disk monitor test passed!" << std::endl;

    return 0;
}
