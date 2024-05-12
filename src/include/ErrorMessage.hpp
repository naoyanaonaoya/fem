#include <stdexcept>
#include <string>

std::string createErroeMessage(const std::string& message, const std::string& file, const int& line) {
    return message + " (File: " + file + ", Line: " + std::to_string(line) + ")";
}