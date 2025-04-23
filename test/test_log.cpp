//
// Purpur Tentakel
// 23.04.25
//


#include <cpt/log.hpp>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <tuple>

class LogLevel : public testing::TestWithParam<std::tuple<cpt::log::Level, std::function<void()>, std::string>> { };

TEST_P(LogLevel, LOG_LEVEL_TRACE) {
    auto const level    = std::get<0>(GetParam());
    auto const func     = std::get<1>(GetParam());
    auto const expected = std::get<2>(GetParam());

    cpt::log::set_level(level);

    std::ostringstream const oss;
    auto* old_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    func();

    std::cout.rdbuf(old_buf);

    auto const output = [&oss]() {
        auto const str = oss.str();
        if (str.size() > 9) {
            return str.substr(9);
        }

        return str;
    }();

    EXPECT_EQ(expected, output);
}

INSTANTIATE_TEST_SUITE_P(LOG,
                         LogLevel,
                         ::testing::Values(
                                 // clang-format off
// trace
std::make_tuple(cpt::log::Level::Trace,    [] { cpt::log::trace("message"); }, "[trace]    message\n"),
std::make_tuple(cpt::log::Level::Debug,    [] { cpt::log::trace("message"); }, ""),
std::make_tuple(cpt::log::Level::Info,     [] { cpt::log::trace("message"); }, ""),
std::make_tuple(cpt::log::Level::Warn,     [] { cpt::log::trace("message"); }, ""),
std::make_tuple(cpt::log::Level::Error,    [] { cpt::log::trace("message"); }, ""),
std::make_tuple(cpt::log::Level::Critical, [] { cpt::log::trace("message"); }, ""),
std::make_tuple(cpt::log::Level::None,     [] { cpt::log::trace("message"); }, ""),
// debug
std::make_tuple(cpt::log::Level::Trace,    [] { cpt::log::debug("message"); }, "[debug]    message\n"),
std::make_tuple(cpt::log::Level::Debug,    [] { cpt::log::debug("message"); }, "[debug]    message\n"),
std::make_tuple(cpt::log::Level::Info,     [] { cpt::log::debug("message"); }, ""),
std::make_tuple(cpt::log::Level::Warn,     [] { cpt::log::debug("message"); }, ""),
std::make_tuple(cpt::log::Level::Error,    [] { cpt::log::debug("message"); }, ""),
std::make_tuple(cpt::log::Level::Critical, [] { cpt::log::debug("message"); }, ""),
std::make_tuple(cpt::log::Level::None,     [] { cpt::log::debug("message"); }, ""),
// info
std::make_tuple(cpt::log::Level::Trace,    [] { cpt::log::info("message"); }, "[Info]     message\n"),
std::make_tuple(cpt::log::Level::Debug,    [] { cpt::log::info("message"); }, "[Info]     message\n"),
std::make_tuple(cpt::log::Level::Info,     [] { cpt::log::info("message"); }, "[Info]     message\n"),
std::make_tuple(cpt::log::Level::Warn,     [] { cpt::log::info("message"); }, ""),
std::make_tuple(cpt::log::Level::Error,    [] { cpt::log::info("message"); }, ""),
std::make_tuple(cpt::log::Level::Critical, [] { cpt::log::info("message"); }, ""),
std::make_tuple(cpt::log::Level::None,     [] { cpt::log::info("message"); }, ""),
// warn
std::make_tuple(cpt::log::Level::Trace,    [] { cpt::log::warn("message"); }, "[Warn]     message\n"),
std::make_tuple(cpt::log::Level::Debug,    [] { cpt::log::warn("message"); }, "[Warn]     message\n"),
std::make_tuple(cpt::log::Level::Info,     [] { cpt::log::warn("message"); }, "[Warn]     message\n"),
std::make_tuple(cpt::log::Level::Warn,     [] { cpt::log::warn("message"); }, "[Warn]     message\n"),
std::make_tuple(cpt::log::Level::Error,    [] { cpt::log::warn("message"); }, ""),
std::make_tuple(cpt::log::Level::Critical, [] { cpt::log::warn("message"); }, ""),
std::make_tuple(cpt::log::Level::None,     [] { cpt::log::warn("message"); }, ""),
// error
std::make_tuple(cpt::log::Level::Trace,    [] { cpt::log::error("message"); }, "[ERROR]    message\n"),
std::make_tuple(cpt::log::Level::Debug,    [] { cpt::log::error("message"); }, "[ERROR]    message\n"),
std::make_tuple(cpt::log::Level::Info,     [] { cpt::log::error("message"); }, "[ERROR]    message\n"),
std::make_tuple(cpt::log::Level::Warn,     [] { cpt::log::error("message"); }, "[ERROR]    message\n"),
std::make_tuple(cpt::log::Level::Error,    [] { cpt::log::error("message"); }, "[ERROR]    message\n"),
std::make_tuple(cpt::log::Level::Critical, [] { cpt::log::error("message"); }, ""),
std::make_tuple(cpt::log::Level::None,     [] { cpt::log::error("message"); }, ""),
// error
std::make_tuple(cpt::log::Level::Trace,    [] { cpt::log::critical("message"); }, "[CRITICAL] message\n"),
std::make_tuple(cpt::log::Level::Debug,    [] { cpt::log::critical("message"); }, "[CRITICAL] message\n"),
std::make_tuple(cpt::log::Level::Info,     [] { cpt::log::critical("message"); }, "[CRITICAL] message\n"),
std::make_tuple(cpt::log::Level::Warn,     [] { cpt::log::critical("message"); }, "[CRITICAL] message\n"),
std::make_tuple(cpt::log::Level::Error,    [] { cpt::log::critical("message"); }, "[CRITICAL] message\n"),
std::make_tuple(cpt::log::Level::Critical, [] { cpt::log::critical("message"); }, "[CRITICAL] message\n"),
std::make_tuple(cpt::log::Level::None,     [] { cpt::log::critical("message"); }, "")
                                 // clang-format on
                                 ));
