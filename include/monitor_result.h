#ifndef MONITOR_RESULT_H
#define MONITOR_RESULT_H

#include <string>

enum class MonitorStatus
{
    OK,
    WARNING,
    CRITICAL
};

struct MonitorResult
{
    std::string name;
    double value;
    MonitorStatus status;
    std::string message;
};

#endif
