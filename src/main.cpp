#include "config_manager.h"
#include "logger.h"

#include <iostream>

int main()
{
    try
    {
        Logger logger("health_monitor.log");

        ConfigManager configManager(
            "../config/health_monitor.json"
        );

        Config config = configManager.load();

        logger.log(
            LogLevel::INFO,
            "Configuration loaded successfully"
        );

        std::cout << "\n--- Configuration ---\n";

        std::cout << "Interval: "
                  << config.intervalSeconds
                  << " seconds\n";

        std::cout << "CPU warning: "
                  << config.cpuWarning
                  << "%\n";

        std::cout << "CPU critical: "
                  << config.cpuCritical
                  << "%\n";

        std::cout << "Memory warning: "
                  << config.memoryWarning
                  << "%\n";

        std::cout << "Memory critical: "
                  << config.memoryCritical
                  << "%\n";

        std::cout << "Disk warning: "
                  << config.diskWarning
                  << "%\n";

        std::cout << "Disk critical: "
                  << config.diskCritical
                  << "%\n";

        std::cout << "Temperature warning: "
                  << config.temperatureWarning
                  << " C\n";

        std::cout << "Temperature critical: "
                  << config.temperatureCritical
                  << " C\n";

        std::cout << "Network interface: "
                  << config.networkInterface
                  << "\n";

        std::cout << "Network host: "
                  << config.networkHost
                  << "\n";

        std::cout << "Critical service: "
                  << config.serviceName
                  << "\n";

        std::cout << "Maximum retries: "
                  << config.serviceMaxRetries
                  << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: "
                  << e.what()
                  << std::endl;

        return 1;
    }

    return 0;
}
