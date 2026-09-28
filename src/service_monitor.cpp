#include "service_monitor.h"

#include <cstdlib>
#include <string>

#include <sys/wait.h>

namespace
{
    int runCommand(const char* command, const char* argument)
    {
        std::string fullCommand =
            std::string(command) + " " + argument +
            " > /dev/null 2>&1";

        return std::system(fullCommand.c_str());
    }

    bool commandSucceeded(int result)
    {
        return result != -1 &&
               WIFEXITED(result) &&
               WEXITSTATUS(result) == 0;
    }
}

MonitorResult ServiceMonitor::check(
    const std::string& serviceName)
{
    int result = runCommand(
        "systemctl is-active",
        serviceName.c_str()
    );

    if (commandSucceeded(result))
    {
        return {
            "Service",
            100.0,
            MonitorStatus::OK,
            serviceName + " is active"
        };
    }

    return {
        "Service",
        0.0,
        MonitorStatus::CRITICAL,
        serviceName + " is inactive"
    };
}

bool ServiceMonitor::recover(
    const std::string& serviceName)
{
    int result = runCommand(
        "systemctl restart",
        serviceName.c_str()
    );

    return commandSucceeded(result);
}
