#include "Utils.h"

std::string Utils::ParseFile(const std::string& filePath) {
    std::ifstream stream(filePath);

    if (!stream.is_open()) {
        CORE_ERROR("File \'{0}\' not found.", filePath);
    }

    std::string line;
    std::stringstream ss;
    while (getline(stream, line)) {
        ss << line << '\n';
    }
    return ss.str();
}