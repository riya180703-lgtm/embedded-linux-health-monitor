#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include "monitor_result.h"
#include <string>

class TemperatureMonitor
{
public:
    MonitorResult check(
        const std::string& path,
        double warning,
        double critical
    );
};

#endif
