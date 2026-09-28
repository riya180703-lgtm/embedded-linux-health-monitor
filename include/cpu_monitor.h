#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include "monitor_result.h"
#include <string>

class CpuMonitor
{
public:
    MonitorResult check(double warning, double critical);

private:
    unsigned long long readTotalJiffies();
    unsigned long long readIdleJiffies();
};

#endif
