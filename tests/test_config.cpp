#include "config_manager.h"

#include <cassert>
#include <iostream>

int main()
{
    ConfigManager configManager("../config/health_monitor.json");
    Config config = configManager.load();

    // Check that the monitoring interval is valid
    assert(config.intervalSeconds > 0);

    // Check CPU thresholds
    assert(config.cpuWarning > 0);
    assert(config.cpuCritical > config.cpuWarning);

    // Check memory thresholds
    assert(config.memoryWarning > 0);
    assert(config.memoryCritical > config.memoryWarning);

    // Check disk thresholds
    assert(config.diskWarning > 0);
    assert(config.diskCritical > config.diskWarning);

    // Check that the network settings are present
    assert(!config.networkInterface.empty());
    assert(!config.networkHost.empty());

    // Check that the service name is present
    assert(!config.serviceName.empty());
    assert(config.serviceMaxRetries > 0);

    std::cout << "Configuration test passed!" << std::endl;

    return 0;
}
