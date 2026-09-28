#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include "monitor_result.h"

class MemoryMonitor
{
public:
    MonitorResult check(double warning, double critical);
};

#endif
