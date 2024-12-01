#include "print_time.h"

std::string get_current_time(bool verbose) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm buf;
    localtime_r(&in_time_t, &buf);

    std::ostringstream oss;
    oss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    std::string timestamp = oss.str();

    if (verbose) {
        std::cout << timestamp << std::endl;
    }

    return timestamp;
}

