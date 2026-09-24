#ifndef LOGGER_H
#define LOGGER_H

#include <string>

enum class LogLevel
{
    INFO,
    WARNING,
    ERROR
};

class Logger
{
public:
    explicit Logger(const std::string& logFile);

    void log(LogLevel level, const std::string& message);

private:
    std::string logFile;

    std::string getTimestamp() const;
    std::string levelToString(LogLevel level) const;
};

#endif
