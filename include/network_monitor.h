#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

#include "monitor_result.h"
#include <string>

class NetworkMonitor
{
public:
    MonitorResult check(
        const std::string& interfaceName,
        const std::string& host
    );
};

#endif
