#include "service_monitor.h"
#include "monitor_result.h"

#include <cassert>
#include <iostream>

int main()
{
    ServiceMonitor serviceMonitor;

    MonitorResult result = serviceMonitor.check("ssh");

    // Verify the monitor name
    assert(result.name == "Service");

    // SSH should be active for this test
    assert(result.status == MonitorStatus::OK);

    std::cout << "Service monitor test passed!" << std::endl;

    return 0;
}
