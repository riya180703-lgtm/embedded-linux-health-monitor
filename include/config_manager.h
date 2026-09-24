#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

struct Config
{
    int intervalSeconds;

    double cpuWarning;
    double cpuCritical;

    double memoryWarning;
    double memoryCritical;

    double diskWarning;
    double diskCritical;

    double temperatureWarning;
    double temperatureCritical;
    std::string temperaturePath;

    std::string networkInterface;
    std::string networkHost;

    std::string serviceName;
    int serviceMaxRetries;
};

class ConfigManager
{
public:
    explicit ConfigManager(const std::string& configPath);

    Config load();

private:
    std::string configPath;
};

#endif
