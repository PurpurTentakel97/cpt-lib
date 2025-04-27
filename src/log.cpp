//
// Purpur Tentakel
// 22.04.25
//

#include <cpt/log.hpp>

namespace cpt {
    bool log::should_print(Level const level) {
        return level >= s_level;
    }

    std::string log::time() {
        auto const now           = std::chrono::system_clock::now();
        auto const local         = std::chrono::current_zone()->to_local(now);
        auto const local_seconds = std::chrono::floor<std::chrono::seconds>(local);
        return std::format(s_format, local_seconds);
    }

    void log::set_level(Level const level) {
        s_level = level;
    }

    void log::set_format(TimePointFormat const& format) {
        s_format = format;
    }

    void log::flush() {
        std::lock_guard lock{ s_mutex };
        std::cout << std::flush;
    }
} // namespace cpt
