//
// Purpur Tentakel
// 21.04.25
//

#pragma once

#include <chrono>
#include <filesystem>
#include <format>
#include <iostream>
#include <mutex>
#include <string>
#include <tl/expected.hpp>
#include <vector>

namespace cpt {
    enum class WriteFileError;
}

namespace cpt {
    class log {
    public:
        enum class Level {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Critical,
            None,
        };

        using TimePointFormat =
                std::format_string<std::chrono::time_point<std::chrono::local_t, std::chrono::seconds> const&>;
        template<typename... Args>
        using MessageFormat = std::format_string<Args...>;


    private:
        struct LogEntry final {
            Level level;
            std::string message;
        };
        static inline std::vector<LogEntry> s_log{};
        static inline std::mutex s_mutex{};
        static inline auto s_level                        = Level::Info;
        static constexpr TimePointFormat s_default_format = "{:%H:%M:%S}";
        static inline TimePointFormat s_format            = s_default_format;
        static constexpr auto s_critical_str              = "[CRITICAL]";
        static constexpr auto s_error_str                 = "[ERROR]   ";
        static constexpr auto s_warn_str                  = "[Warn]    ";
        static constexpr auto s_info_str                  = "[Info]    ";
        static constexpr auto s_debug_str                 = "[debug]   ";
        static constexpr auto s_trace_str                 = "[trace]   ";

        static bool should_log(Level current, Level provided);

        static std::string time(TimePointFormat const& format);

        template<typename... Args>
        static void print(Level const level,
                          std::string const& level_text,
                          std::format_string<Args...> const message,
                          Args&&... args) {
            auto const to_print = std::format(
                    "{} {} {}\n", time(s_format), level_text, std::format(message, std::forward<Args>(args)...));
            std::lock_guard lock{ s_mutex };

            s_log.push_back({ level, to_print });

            if (should_log(s_level, level)) {
                std::cout << to_print;
            }
        }

    public:
        /**
         *
         * @param level highest level that's going to be logged.
         */
        static void set_level(Level level);
        /**
         *
         * @param format that's used to print the timestamp. Use 'std::format'.
         */
        static void set_format(TimePointFormat const& format);

        /**
         * calls std::flush.
         */
        static void flush();

        /**
         *
         * @param level minimum level that gets dumped
         * @return dump as string
         */
        [[nodiscard]] static std::string dump(Level level);
        /**
         *
         * @param level minimum level that gets dumped
         * @param path relative or absolute path the pump gets saved to
         * @return if the save was successful
         */
        static tl::expected<void, WriteFileError> save(Level level, std::filesystem::path const& path);

        /**
         * clears the current log map.
         */
        static void clear();
        /**
         * resets the format sting for the log timestamp.
         */
        static void reset_format();

        /**
         *  if the logging level is set higher than 'critical' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_critical(MessageFormat<Args...> const& message, Args&&... args) {
            print(Level::Critical, s_critical_str, message, std::forward<Args>(args)...);
        }
        /**
         *  if the logging level is set higher than 'critical' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void critical([[maybe_unused]] MessageFormat<Args...> const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_critical(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'error' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_error(MessageFormat<Args...> const& message, Args&&... args) {
            print(Level::Error, s_error_str, message, std::forward<Args>(args)...);
        }
        /**
         *  if the logging level is set higher than 'error' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void error([[maybe_unused]] MessageFormat<Args...> const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_error(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'warn' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_warn(MessageFormat<Args...> const& message, Args&&... args) {
            print(Level::Warn, s_warn_str, message, std::forward<Args>(args)...);
        }
        /**
         *  if the logging level is set higher than 'warn' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void warn([[maybe_unused]] MessageFormat<Args...> const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_warn(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'info' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_info(MessageFormat<Args...> const& message, Args&&... args) {
            print(Level::Info, s_info_str, message, std::forward<Args>(args)...);
        }
        /**
         *  if the logging level is set higher than 'info' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void info([[maybe_unused]] MessageFormat<Args...> const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_info(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'debug' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_debug(MessageFormat<Args...> const& message, Args&&... args) {
            print(Level::Debug, s_debug_str, message, std::forward<Args>(args)...);
        }
        /**
         *  if the logging level is set higher than 'debug' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void debug([[maybe_unused]] MessageFormat<Args...> const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_debug(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'trace' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_trace(MessageFormat<Args...> const& message, Args&&... args) {
            print(Level::Trace, s_trace_str, message, std::forward<Args>(args)...);
        }
        /**
         *  if the logging level is set higher than 'trace' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::format`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void trace([[maybe_unused]] MessageFormat<Args...> const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_trace(message, std::forward<Args>(args)...);
#endif
        }
    };
} // namespace cpt
