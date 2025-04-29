#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    explicit Logger(const std::string& filename);//init
    ~Logger();//fermeture du fichier

    void log(LogLevel level, const std::string& message);

    static std::string logLevelToString(LogLevel level);

private:
    std::ofstream logFile;
    std::string filename;
    std::mutex logMutex;  // Protection pour usage multi-thread
};