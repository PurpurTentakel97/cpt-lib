//
// Purpur Tentakel
// 22.04.25
//

#include <chrono>
#include <cpt/log.hpp>

namespace cpt {
    bool log::should_print(Level const level) {
        return level >= s_level;
    }

    std::string log::time() {
        try {
            auto const now           = std::chrono::system_clock::now();
            auto const local         = std::chrono::current_zone()->to_local(now);
            auto const local_seconds = std::chrono::floor<std::chrono::seconds>(local);
            return std::vformat(s_format, std::make_format_args(local_seconds));
        } catch (std::format_error const& e) {
            std::lock_guard lock{ s_mutex };
            std::cerr << "Error while formatting timestamp: '" << s_format << "'\n"
                      << "error: '" << e.what() << "'\n"
                      << std::flush;
            return "TIMESTAMP";
        } catch (std::bad_alloc const& e) {
            std::lock_guard lock{ s_mutex };
            std::cerr << "bad alloc while printing timestamp: '" << s_format << "'\n"
                      << "error: '" << e.what() << "'\n"
                      << std::flush;
            return "TIMESTAMP";
        }
    }

    void log::set_level(Level const level) {
        s_level = level;
    }

    void log::set_format(std::string const& format) {
        s_format = format;
    }
} // namespace cpt
