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

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Unable to open configuration file: " + configPath
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

    return config;
}

