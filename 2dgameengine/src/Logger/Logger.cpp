#include "Logger.hpp"
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

std::vector<LogEntry> Logger::messages;

void Logger::Log(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    
    
    time_t now = time(0);
    char* dt = ctime(&now);
 
    // Remove newline character that ctime appends
    dt[strlen(dt) - 1] = '\0';
    logEntry.message = std::string("LOG | ") + dt + " : " + message;
    std::cout << "\033[32m" << logEntry.message << "\033[0m" << "\n" << std::flush;
    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
    time_t now = time(0);
    char* dt = ctime(&now);

    // Remove newline character that ctime appends
    dt[strlen(dt) - 1] = '\0';

    std::cout << "\033[31m" << "ERR | " << dt << " : " << message << "\033[0m" << "\n" << std::flush;
}
