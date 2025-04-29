#include "Logger.h"

Logger::Logger(const std::string& filename) : filename(filename) {
    logFile.open(filename, std::ios::out | std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Erreur d'ouverture du fichier de log: " << filename << std::endl;
        return;
    }

    if (logFile.tellp() == 0) {//si fichier vide
        logFile << "Level,Message\n";  // Ajout de l'en-tête uniquement si le fichier est vide
        logFile.flush();  // Force l'écriture immédiate
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);  // Sécurisation en cas d'accès multi-thread

    if (!logFile.is_open()) {
        std::cerr << "Erreur : fichier de log non ouvert." << std::endl;
        return;
    }

    logFile << logLevelToString(level) << "," << message << "\n";
    logFile.flush();  // Force l'écriture immédiate pour éviter la perte de logs
}

std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::INFO:    return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::ERROR:   return "ERROR";
    default:                return "UNKNOWN";
    }
}