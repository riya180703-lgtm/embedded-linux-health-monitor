#include "config_manager.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

ConfigManager::ConfigManager(const std::string& path)
    : configPath(path)
{
}

Config ConfigManager::load()
{
    std::ifstream file(configPath);

    if (!file)
    {
        throw std::runtime_error(
            "Cannot open config file: " + configPath
        );
    }

    json data;
    file >> data;

    Config config{};

    config.intervalSeconds =
        data.at("interval_seconds").get<int>();

    config.cpuWarning =
        data.at("cpu").at("warning").get<double>();

    config.cpuCritical =
        data.at("cpu").at("critical").get<double>();

    config.memoryWarning =
        data.at("memory").at("warning").get<double>();

    config.memoryCritical =
        data.at("memory").at("critical").get<double>();

    config.diskWarning =
        data.at("disk").at("warning").get<double>();

    config.diskCritical =
        data.at("disk").at("critical").get<double>();

    config.temperatureWarning =
        data.at("temperature").at("warning").get<double>();

    config.temperatureCritical =
        data.at("temperature").at("critical").get<double>();

    config.temperaturePath =
        data.at("temperature").at("path").get<std::string>();

    config.networkInterface =
        data.at("network").at("interface").get<std::string>();

    config.networkHost =
        data.at("network").at("host").get<std::string>();

    config.serviceName =
        data.at("service").at("name").get<std::string>();

    config.serviceMaxRetries =
        data.at("service").at("max_retries").get<int>();
    // Validate monitoring interval
    if (config.intervalSeconds <= 0)
    {
        throw std::invalid_argument(
            "Monitoring interval must be greater than zero");
    }

    // Validate warning and critical thresholds
    auto validateThresholds = [](double warning,
                                 double critical,
                                 const std::string& name)
    {
        if (warning < 0 || warning > 100 ||
            critical < 0 || critical > 100)
        {
            throw std::invalid_argument(
                name + " thresholds must be between 0 and 100");
        }

        if (warning >= critical)
        {
            throw std::invalid_argument(
                name + " warning threshold must be less than critical");
        }
    };

    validateThresholds(
        config.cpuWarning, config.cpuCritical, "CPU");

    validateThresholds(
        config.memoryWarning, config.memoryCritical, "Memory");

    validateThresholds(
        config.diskWarning, config.diskCritical, "Disk");

    validateThresholds(
        config.temperatureWarning,
        config.temperatureCritical,
        "Temperature");

    // Validate network configuration
    if (config.networkInterface.empty() ||
        config.networkHost.empty())
    {
        throw std::invalid_argument(
            "Network interface and host must not be empty");
    }

    // Validate service configuration
    if (config.serviceName.empty())
    {
        throw std::invalid_argument(
            "Service name must not be empty");
    }

    if (config.serviceMaxRetries < 0)
    {
        throw std::invalid_argument(
            "Maximum service retries cannot be negative");
    }
    return config;
}
