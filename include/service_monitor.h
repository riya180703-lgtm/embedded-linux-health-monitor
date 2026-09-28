#ifndef SERVICE_MONITOR_H
#define SERVICE_MONITOR_H

#include "monitor_result.h"
#include <string>

class ServiceMonitor
{
public:
    MonitorResult check(const std::string& serviceName);

    bool recover(const std::string& serviceName);
};

#endif
