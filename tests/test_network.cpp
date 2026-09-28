#include "network_monitor.h"
#include "monitor_result.h"

#include <cassert>
#include <iostream>

int main()
{
    NetworkMonitor networkMonitor;

    MonitorResult result =
        networkMonitor.check("eth0", "8.8.8.8");

    // Verify the monitor name
    assert(result.name == "Network");

    // Verify the reported value is valid
    assert(result.value >= 0.0);
    assert(result.value <= 100.0);

    // Verify that the monitor returned a valid status
    assert(result.status == MonitorStatus::OK ||
           result.status == MonitorStatus::WARNING ||
           result.status == MonitorStatus::CRITICAL);

    // Verify that a message was returned
    assert(!result.message.empty());

    std::cout << "Network monitor test passed!" << std::endl;

    return 0;
}
