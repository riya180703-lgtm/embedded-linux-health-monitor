#include "temperature_monitor.h"
#include "monitor_result.h"

#include <cassert>
#include <iostream>

int main()
{
    TemperatureMonitor temperatureMonitor;

    // Use a path that should not exist
    MonitorResult result = temperatureMonitor.check(
        "/tmp/nonexistent_temperature_sensor",
        70,
        85
    );

    // Verify the monitor name
    assert(result.name == "Temperature");

    // An unavailable sensor should produce a warning
    assert(result.status == MonitorStatus::WARNING);

    // Verify that an explanatory message is returned
    assert(!result.message.empty());

    std::cout << "Temperature monitor test passed!" << std::endl;

    return 0;
}
