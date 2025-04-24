//
// Purpur Tentakel
// 21.04.25
//

#pragma once

#include <format>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <utility>

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

    private:
        static inline std::mutex s_mutex{};
        static inline auto s_level           = Level::Info;
        static inline std::string s_format   = "{:%H:%M:%S}";
        static constexpr auto s_critical_str = "[CRITICAL]";
        static constexpr auto s_error_str    = "[ERROR]   ";
        static constexpr auto s_warn_str     = "[Warn]    ";
        static constexpr auto s_info_str     = "[Info]    ";
        static constexpr auto s_debug_str    = "[debug]   ";
        static constexpr auto s_trace_str    = "[trace]   ";

        static bool should_print(Level level);

        static std::string time();

        template<typename... Args>
        static void print(std::string const& level_text, std::string const& message, Args&&... args) {
            try {
                auto const to_print = std::format(
                        "{} {} {}\n", time(), level_text, std::vformat(message, std::make_format_args(args...)));

                std::lock_guard lock{ s_mutex };
                std::cout << to_print;

            } catch (std::format_error const& e) {
                std::stringstream stream{};
                stream << "Error while formatting message: '" << message << "' | Args count: " << sizeof...(args)
                       << "\n"
                       << "error: '" << e.what() << "'\n";
                std::lock_guard lock{ s_mutex };
                std::cerr << stream.str();

            } catch (std::bad_alloc const& e) {
                std::stringstream stream{};
                stream << "bad alloc while printing message: '" << message << "' | Args count: " << sizeof...(args)
                       << '\n'
                       << "error: '" << e.what() << "'\n";
                std::lock_guard lock{ s_mutex };
                std::cerr << stream.str();
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
         * @param format that's used to print the timestamp. Use 'std::vformat'.
         */
        static void set_format(std::string const& format);

        /**
         *  if the logging level is set higher than 'critical' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_critical(std::string const& message, Args&&... args) {
            if (should_print(Level::Critical)) {
                print(s_critical_str, message, std::forward<Args>(args)...);
            }
        }
        /**
         *  if the logging level is set higher than 'critical' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void critical([[maybe_unused]] std::string const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_critical(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'error' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_error(std::string const& message, Args&&... args) {
            if (should_print(Level::Error)) {
                print(s_error_str, message, std::forward<Args>(args)...);
            }
        }
        /**
         *  if the logging level is set higher than 'error' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void error([[maybe_unused]] std::string const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_error(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'warn' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_warn(std::string const& message, Args&&... args) {
            if (should_print(Level::Warn)) {
                print(s_warn_str, message, std::forward<Args>(args)...);
            }
        }
        /**
         *  if the logging level is set higher than 'warn' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void warn([[maybe_unused]] std::string const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_warn(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'info' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_info(std::string const& message, Args&&... args) {
            if (should_print(Level::Info)) {
                print(s_info_str, message, std::forward<Args>(args)...);
            }
        }
        /**
         *  if the logging level is set higher than 'info' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void info([[maybe_unused]] std::string const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_info(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'debug' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_debug(std::string const& message, Args&&... args) {
            if (should_print(Level::Debug)) {
                print(s_debug_str, message, std::forward<Args>(args)...);
            }
        }
        /**
         *  if the logging level is set higher than 'debug' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void debug([[maybe_unused]] std::string const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_debug(message, std::forward<Args>(args)...);
#endif
        }

        /**
         *  if the logging level is set higher than 'trace' this logging gets ignored.
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void r_trace(std::string const& message, Args&&... args) {
            if (should_print(Level::Trace)) {
                print(s_trace_str, message, std::forward<Args>(args)...);
            }
        }
        /**
         *  if the logging level is set higher than 'trace' this logging gets ignored.
         *  gets removed in non debug builds
         *
         * @tparam Args Any datatype, that can be handled by 'std::vformat'
         * @param message logging message, use `std::vformat`
         * @param args that gets formatted into the message
         */
        template<typename... Args>
        static void trace([[maybe_unused]] std::string const& message, [[maybe_unused]] Args&&... args) {
#ifndef NDEBUG
            r_trace(message, std::forward<Args>(args)...);
#endif
        }
    };
} // namespace cpt
