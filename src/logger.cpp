#include "logger.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

Logger::Logger(const std::string& file)
    : logFile(file)
{
}

std::string Logger::getTimestamp() const
{
    auto now = std::chrono::system_clock::now();

    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

    localtime_r(&currentTime, &localTime);

    std::ostringstream output;

    output << std::put_time(
        &localTime,
        "%Y-%m-%d %H:%M:%S"
    );

    return output.str();
}

std::string Logger::levelToString(LogLevel level) const
{
    switch (level)
    {
        case LogLevel::INFO:
            return "INFO";

        case LogLevel::WARNING:
            return "WARNING";

        case LogLevel::ERROR:
            return "ERROR";
    }

    return "UNKNOWN";
}

void Logger::log(
    LogLevel level,
    const std::string& message)
{
    std::string output =
        getTimestamp() +
        " [" +
        levelToString(level) +
        "] " +
        message;

    // Display on terminal
    std::cout << output << std::endl;

    // Also save to file
    std::ofstream file(
        logFile,
        std::ios::app
    );

    if (file)
    {
        file << output << std::endl;
    }
}
