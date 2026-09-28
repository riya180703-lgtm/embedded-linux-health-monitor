#include "cpu_monitor.h"
#include "monitor_result.h"

#include <cassert>
#include <iostream>

int main()
{
    CpuMonitor cpuMonitor;

    MonitorResult result = cpuMonitor.check(70, 90);

    // Verify the monitor name
    assert(result.name == "CPU");

    // CPU usage must be between 0 and 100 percent
    assert(result.value >= 0.0);
    assert(result.value <= 100.0);

    // Verify that the monitor returned a valid status
    assert(result.status == MonitorStatus::OK ||
           result.status == MonitorStatus::WARNING ||
           result.status == MonitorStatus::CRITICAL);

    std::cout << "CPU monitor test passed!" << std::endl;

    return 0;
}
