#include "network_monitor.h"

#include <fstream>
#include <string>

#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>

MonitorResult NetworkMonitor::check(
    const std::string& interfaceName,
    const std::string& host)
{
    // Check whether the network interface is up.
    std::string path =
        "/sys/class/net/" + interfaceName + "/operstate";

    std::ifstream file(path);
    std::string state;

    if (!file || !(file >> state))
    {
        return {
            "Network",
            0.0,
            MonitorStatus::CRITICAL,
            "Unable to read network interface state"
        };
    }

    if (state != "up")
    {
        return {
            "Network",
            0.0,
            MonitorStatus::CRITICAL,
            "Network interface is not up: " + state
        };
    }

    // Check connectivity by sending one ping.
    pid_t pid = fork();

    if (pid == 0)
    {
        execlp(
            "ping",
            "ping",
            "-c", "1",
            "-W", "2",
            host.c_str(),
            static_cast<char*>(nullptr)
        );

        _exit(127);
    }

    if (pid < 0)
    {
        return {
            "Network",
            0.0,
            MonitorStatus::CRITICAL,
            "Unable to start ping"
        };
    }

    int status = 0;

    if (waitpid(pid, &status, 0) < 0)
    {
        return {
            "Network",
            0.0,
            MonitorStatus::CRITICAL,
            "Unable to wait for ping"
        };
    }

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
    {
        return {
            "Network",
            100.0,
            MonitorStatus::OK,
            "Network interface is up and host is reachable"
        };
    }

    return {
        "Network",
        0.0,
        MonitorStatus::CRITICAL,
        "Host is unreachable: " + host
    };
}
