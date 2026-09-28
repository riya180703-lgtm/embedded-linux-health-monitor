#include "config_manager.h"
#include "monitor_result.h"
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "disk_monitor.h"
#include "temperature_monitor.h"
#include "network_monitor.h"
#include "service_monitor.h"
#include "logger.h"

#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <thread>

void displayResult(const MonitorResult& result, Logger& logger)
{
    std::string status;
    std::string unit = "%";
    LogLevel level = LogLevel::INFO;

    switch (result.status)
    {
        case MonitorStatus::OK:
            status = "OK";
            break;

        case MonitorStatus::WARNING:
            status = "WARNING";
            level = LogLevel::WARNING;
            break;

        case MonitorStatus::CRITICAL:
            status = "CRITICAL";
            level = LogLevel::ERROR;
            break;
    }

    if (result.name == "Temperature")
        unit = " C";

    std::string message =
        result.name + ": " +
        std::to_string(result.value) + unit +
        " [" + status + "] - " +
        result.message;

    std::cout << message << '\n';
    logger.log(level, message);
}

int main()
{
    try
    {
        Logger logger("health_monitor.log");

        ConfigManager configManager(
            "../config/health_monitor.json"
        );

        Config config = configManager.load();

        CpuMonitor cpuMonitor;
        MemoryMonitor memoryMonitor;
        DiskMonitor diskMonitor;
        TemperatureMonitor temperatureMonitor;
        NetworkMonitor networkMonitor;
        ServiceMonitor serviceMonitor;

        // Automatic recovery settings
        const int failureThreshold = 3;
        const int cooldownSeconds = 30;

        int consecutiveFailures = 0;
        int recoveryAttempts = 0;

        logger.log(
            LogLevel::INFO,
            "Embedded Linux Health Monitor started"
        );

        while (true)
        {
            std::cout << "\n--- System Health Check ---\n";

            displayResult(
                cpuMonitor.check(
                    config.cpuWarning,
                    config.cpuCritical
                ),
                logger
            );

            displayResult(
                memoryMonitor.check(
                    config.memoryWarning,
                    config.memoryCritical
                ),
                logger
            );

            displayResult(
                diskMonitor.check(
                    config.diskWarning,
                    config.diskCritical
                ),
                logger
            );

            displayResult(
                temperatureMonitor.check(
                    config.temperaturePath,
                    config.temperatureWarning,
                    config.temperatureCritical
                ),
                logger
            );

            displayResult(
                networkMonitor.check(
                    config.networkInterface,
                    config.networkHost
                ),
                logger
            );

            // Check the critical service
            MonitorResult serviceResult =
                serviceMonitor.check(config.serviceName);

            displayResult(serviceResult, logger);

            if (serviceResult.status == MonitorStatus::OK)
            {
                consecutiveFailures = 0;
                recoveryAttempts = 0;
            }
            else
            {
                consecutiveFailures++;

                logger.log(
                    LogLevel::WARNING,
                    "Service failure count: " +
                    std::to_string(consecutiveFailures)
                );

                if (consecutiveFailures >= failureThreshold)
                {
                    if (recoveryAttempts < config.serviceMaxRetries)
                    {
                        recoveryAttempts++;

                        logger.log(
                            LogLevel::WARNING,
                            "Attempting service recovery: " +
                            std::to_string(recoveryAttempts)
                        );

                        bool recovered =
                            serviceMonitor.recover(config.serviceName);

                        if (recovered)
                        {
                            logger.log(
                                LogLevel::INFO,
                                "Service restart command succeeded"
                            );
                        }
                        else
                        {
                            logger.log(
                                LogLevel::ERROR,
                                "Service restart failed"
                            );
                        }

                        std::this_thread::sleep_for(
                            std::chrono::seconds(cooldownSeconds)
                        );
                    }
                    else
                    {
                        logger.log(
                            LogLevel::ERROR,
                            "Maximum recovery attempts reached"
                        );
                    }
                }
            }

            std::this_thread::sleep_for(
                std::chrono::seconds(config.intervalSeconds)
            );
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
