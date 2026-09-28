#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

#include "monitor_result.h"

class DiskMonitor
{
public:
    MonitorResult check(double warning, double critical);
};

#endif
