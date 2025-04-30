//
// Purpur Tentakel
// 22.04.25
//

#include <cpt/files.hpp>
#include <cpt/log.hpp>

namespace cpt {
    bool log::should_log(Level const current, Level const provided) {
        return provided >= current;
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

    std::string log::dump(Level const level) {
        std::string to_return{};
        std::lock_guard lock{ s_mutex };

        for (auto const& [lv, msg] : s_log) {
            if (not should_log(level, lv)) {
                continue;
            }
            to_return += msg;
        }

        return to_return;
    }

    tl::expected<void, WriteFileError> log::save(Level const level, std::filesystem::path const& path) {
        auto const result = cpt::write_file(path, dump(level));
        if (!result.has_value()) {
            switch (result.error()) {
                case WriteFileError::OpenFile: {
                    r_critical("unable to open logfile: {}", path.string());
                    break;
                }
                case WriteFileError::WriteToFile: {
                    r_critical("unable to write to logfile: {}", path.string());
                    break;
                }
                default: {
                    r_critical("unexpected error while saving log to: {}", path.string());
                    break;
                }
            }
        }

        return result;
    }
    void log::clear() {
        s_log.clear();
    }
} // namespace cpt
