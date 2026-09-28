#include "temperature_monitor.h"

#include <fstream>
#include <string>

MonitorResult TemperatureMonitor::check(
    const std::string& path,
    double warning,
    double critical)
{
    std::ifstream file(path);

    if (!file)
    {
        return {
            "Temperature",
            0.0,
            MonitorStatus::WARNING,
            "Temperature sensor unavailable"
        };
    }

    double temperature = 0.0;
    file >> temperature;

    if (file.fail())
    {
        return {
            "Temperature",
            0.0,
            MonitorStatus::WARNING,
            "Unable to read temperature"
        };
    }

    // Linux thermal-zone readings are commonly in millidegrees Celsius.
    if (temperature > 1000.0)
    {
        temperature /= 1000.0;
    }

    MonitorStatus status = MonitorStatus::OK;
    std::string message = "Temperature normal";

    if (temperature >= critical)
    {
        status = MonitorStatus::CRITICAL;
        message = "Temperature critical";
    }
    else if (temperature >= warning)
    {
        status = MonitorStatus::WARNING;
        message = "Temperature high";
    }

    return {
        "Temperature",
        temperature,
        status,
        message
    };
}
