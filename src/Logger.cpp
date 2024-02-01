#include "Logger.h"

#include <sstream>
#include <iomanip>
#include <algorithm>

std::string Logger::parseFileName(const char *logType, const char *filePath) {
    std::string src = filePath;
    std::string ans;

    int i = (int) src.size() - 1;
    while (src[i] != '\\' && src[i] != '/') {
        ans.push_back(src[i]);
        --i;
    }

    ans += "[";

    std::reverse(ans.begin(), ans.end());

    ans += "]";

    std::ostringstream oss;
    oss << std::left << std::setw(15) << std::setfill(' ') << logType;

    oss << std::left << std::setw(30) << std::setfill(' ') << ans;

    return oss.str();
}