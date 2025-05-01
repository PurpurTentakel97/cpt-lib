//
// Purpur Tentakel
// 23.04.25
//


#include <array>
#include <cpt/log.hpp>
#include <cpt/strings.hpp>
#include <cpt/types.hpp>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <regex>
#include <tuple>

struct BasicLogLevelValues final {
    cpt::log::Level const level;
    std::function<void()> const print_debug;
    std::function<void()> const print_release;
    std::string const result;
};

class LogLevel : public testing::TestWithParam<BasicLogLevelValues> { };

TEST_P(LogLevel, LOG_LEVEL) {
    cpt::log::clear();
    // testing debug call
    auto const& params = GetParam();

    cpt::log::set_level(params.level);

    std::ostringstream oss{};
    auto* old_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    params.print_debug();

    auto const output_debug = [&oss]() {
        auto str = oss.str();
        if (str.size() > 9) {
            return str.substr(9);
        }

        return str;
    }();

#ifndef NDEBUG
    EXPECT_EQ(params.result, output_debug);
#else
    EXPECT_EQ("", output_debug);
#endif

    // testing release call
    oss = std::ostringstream{};
    std::cout.rdbuf(oss.rdbuf());

    params.print_release();

    auto const output_release = [&oss]() {
        auto str = oss.str();
        if (str.size() > 9) {
            return str.substr(9);
        }

        return str;
    }();

    EXPECT_EQ(params.result, output_release);

    std::cout.rdbuf(old_buf);
}

INSTANTIATE_TEST_SUITE_P(LOG,
                         LogLevel,
                         ::testing::Values(
                                 // trace
                                 BasicLogLevelValues{ cpt::log::Level::Trace,
                                                      [] { cpt::log::trace("message"); },
                                                      [] { cpt::log::r_trace("message"); },
                                                      "[trace]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Debug,
                                                      [] { cpt::log::trace("message"); },
                                                      [] { cpt::log::r_trace("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Info,
                                                      [] { cpt::log::trace("message"); },
                                                      [] { cpt::log::r_trace("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Warn,
                                                      [] { cpt::log::trace("message"); },
                                                      [] { cpt::log::r_trace("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Error,
                                                      [] { cpt::log::trace("message"); },
                                                      [] { cpt::log::r_trace("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Critical,
                                                      [] { cpt::log::trace("message"); },
                                                      [] { cpt::log::r_trace("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::None,
                                                      [] { cpt::log::trace("message"); },
                                                      [] { cpt::log::r_trace("message"); },
                                                      "" },

                                 // debug
                                 BasicLogLevelValues{ cpt::log::Level::Trace,
                                                      [] { cpt::log::debug("message"); },
                                                      [] { cpt::log::r_debug("message"); },
                                                      "[debug]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Debug,
                                                      [] { cpt::log::debug("message"); },
                                                      [] { cpt::log::r_debug("message"); },
                                                      "[debug]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Info,
                                                      [] { cpt::log::debug("message"); },
                                                      [] { cpt::log::r_debug("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Warn,
                                                      [] { cpt::log::debug("message"); },
                                                      [] { cpt::log::r_debug("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Error,
                                                      [] { cpt::log::debug("message"); },
                                                      [] { cpt::log::r_debug("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Critical,
                                                      [] { cpt::log::debug("message"); },
                                                      [] { cpt::log::r_debug("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::None,
                                                      [] { cpt::log::debug("message"); },
                                                      [] { cpt::log::r_debug("message"); },
                                                      "" },

                                 // info
                                 BasicLogLevelValues{ cpt::log::Level::Trace,
                                                      [] { cpt::log::info("message"); },
                                                      [] { cpt::log::r_info("message"); },
                                                      "[Info]     message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Debug,
                                                      [] { cpt::log::info("message"); },
                                                      [] { cpt::log::r_info("message"); },
                                                      "[Info]     message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Info,
                                                      [] { cpt::log::info("message"); },
                                                      [] { cpt::log::r_info("message"); },
                                                      "[Info]     message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Warn,
                                                      [] { cpt::log::info("message"); },
                                                      [] { cpt::log::r_info("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Error,
                                                      [] { cpt::log::info("message"); },
                                                      [] { cpt::log::r_info("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Critical,
                                                      [] { cpt::log::info("message"); },
                                                      [] { cpt::log::r_info("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::None,
                                                      [] { cpt::log::info("message"); },
                                                      [] { cpt::log::r_info("message"); },
                                                      "" },


                                 // warn
                                 BasicLogLevelValues{ cpt::log::Level::Trace,
                                                      [] { cpt::log::warn("message"); },
                                                      [] { cpt::log::r_warn("message"); },
                                                      "[Warn]     message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Debug,
                                                      [] { cpt::log::warn("message"); },
                                                      [] { cpt::log::r_warn("message"); },
                                                      "[Warn]     message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Info,
                                                      [] { cpt::log::warn("message"); },
                                                      [] { cpt::log::r_warn("message"); },
                                                      "[Warn]     message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Warn,
                                                      [] { cpt::log::warn("message"); },
                                                      [] { cpt::log::r_warn("message"); },
                                                      "[Warn]     message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Error,
                                                      [] { cpt::log::warn("message"); },
                                                      [] { cpt::log::r_warn("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::Critical,
                                                      [] { cpt::log::warn("message"); },
                                                      [] { cpt::log::r_warn("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::None,
                                                      [] { cpt::log::warn("message"); },
                                                      [] { cpt::log::r_warn("message"); },
                                                      "" },


                                 // error
                                 BasicLogLevelValues{ cpt::log::Level::Trace,
                                                      [] { cpt::log::error("message"); },
                                                      [] { cpt::log::r_error("message"); },
                                                      "[ERROR]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Debug,
                                                      [] { cpt::log::error("message"); },
                                                      [] { cpt::log::r_error("message"); },
                                                      "[ERROR]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Info,
                                                      [] { cpt::log::error("message"); },
                                                      [] { cpt::log::r_error("message"); },
                                                      "[ERROR]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Warn,
                                                      [] { cpt::log::error("message"); },
                                                      [] { cpt::log::r_error("message"); },
                                                      "[ERROR]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Error,
                                                      [] { cpt::log::error("message"); },
                                                      [] { cpt::log::r_error("message"); },
                                                      "[ERROR]    message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Critical,
                                                      [] { cpt::log::error("message"); },
                                                      [] { cpt::log::r_error("message"); },
                                                      "" },
                                 BasicLogLevelValues{ cpt::log::Level::None,
                                                      [] { cpt::log::error("message"); },
                                                      [] { cpt::log::r_error("message"); },
                                                      "" },


                                 // critical
                                 BasicLogLevelValues{ cpt::log::Level::Trace,
                                                      [] { cpt::log::critical("message"); },
                                                      [] { cpt::log::r_critical("message"); },
                                                      "[CRITICAL] message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Debug,
                                                      [] { cpt::log::critical("message"); },
                                                      [] { cpt::log::r_critical("message"); },
                                                      "[CRITICAL] message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Info,
                                                      [] { cpt::log::critical("message"); },
                                                      [] { cpt::log::r_critical("message"); },
                                                      "[CRITICAL] message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Warn,
                                                      [] { cpt::log::critical("message"); },
                                                      [] { cpt::log::r_critical("message"); },
                                                      "[CRITICAL] message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Error,
                                                      [] { cpt::log::critical("message"); },
                                                      [] { cpt::log::r_critical("message"); },
                                                      "[CRITICAL] message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::Critical,
                                                      [] { cpt::log::critical("message"); },
                                                      [] { cpt::log::r_critical("message"); },
                                                      "[CRITICAL] message\n" },
                                 BasicLogLevelValues{ cpt::log::Level::None,
                                                      [] { cpt::log::critical("message"); },
                                                      [] { cpt::log::r_critical("message"); },
                                                      "" }));

struct TimePointLogValues final {
    cpt::log::TimePointFormat const format;
    std::string regex_str;

    explicit TimePointLogValues(cpt::log::TimePointFormat const format_, std::string regex_str_)
        : format{ format_ },
          regex_str{ std::move(regex_str_) } { }
};

class TimePointLog : public testing::TestWithParam<TimePointLogValues> { };

TEST_P(TimePointLog, TIME_POINT) {
    cpt::log::clear();
    auto const& params = GetParam();

    std::ostringstream const oss{};
    auto* old_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    cpt::log::set_level(cpt::log::Level::Info);
    cpt::log::set_format(params.format);
    cpt::log::r_info("");

    auto const printed = oss.str();

    EXPECT_TRUE(std::regex_match(printed, std::regex{ params.regex_str }))
            << '\n'
            << "time_stamp_format: '" << params.format.get() << "'\n"
            << "regex: '" << params.regex_str << "'\n"
            << "printed_message: '" << printed << "'\n";

    std::cout.rdbuf(old_buf);
}

INSTANTIATE_TEST_SUITE_P(TIME_POINT,
                         TimePointLog,
                         ::testing::Values(TimePointLogValues{ "{:%H:%M:%S}", "\\d\\d:\\d\\d:\\d\\d.+\\n" },
                                           TimePointLogValues{
                                                   "{:%d.%m.%Y %H:%M:%S}",
                                                   "\\d\\d\\.\\d\\d\\.\\d\\d\\d\\d \\d\\d:\\d\\d:\\d\\d.+\\n" }));


TEST(LOG, PARAMS) {
    cpt::log::clear();
    cpt::log::set_level(cpt::log::Level::Info);
    cpt::log::r_info("{}", 1);
    cpt::log::r_info("{}", 1, "hi");
    cpt::log::r_info("{0} {1} {0}", 1, "hi");
}

struct DumpLogValues final {
    cpt::log::Level dump_level;
    int count;
};

class DumpLog : public testing::TestWithParam<DumpLogValues> { };

TEST_P(DumpLog, DUMP) {

    auto const expected = std::array<std::string, 6>{
        "[trace]", "[debug]", "[Info]", "[Warn]", "[ERROR]", "[CRITICAL]",
    };

    cpt::log::clear();
    cpt::log::set_level(cpt::log::Level::Info);

    auto const& params = GetParam();

    cpt::log::r_trace("message");
    cpt::log::r_debug("message");
    cpt::log::r_info("message");
    cpt::log::r_warn("message");
    cpt::log::r_error("message");
    cpt::log::r_critical("message");

    auto const dump = cpt::log::dump(params.dump_level);

    auto const single_lines = cpt::split(dump, "\n", cpt::SplitBehavior::SkipEmptyParts);
    auto const enum_index   = static_cast<cpt::usize>(params.dump_level);

    EXPECT_EQ(params.count, single_lines.size())
            << "unexpected line count: expected: '" << params.count << "'; provided: '" << single_lines.size() << "'\n";

    for (cpt::usize i = 0; i < expected.size() - enum_index; ++i) {
        auto const dump_entries = cpt::split(single_lines[i], " ", cpt::SplitBehavior::SkipEmptyParts);
        auto const& ex_type     = expected[i + enum_index];
        EXPECT_EQ(dump_entries[2], ex_type) << "unexpected log type: expected: '" << ex_type << "'; provided: '" << dump_entries[2] << "'\n";
        EXPECT_EQ(dump_entries[3], "message")<< "unexpected log message: expected: 'message'; provided: '" << dump_entries[2] << "\n";
    }
}


INSTANTIATE_TEST_SUITE_P(DUMP,
                         DumpLog,
                         ::testing::Values(DumpLogValues{ cpt::log::Level::Trace, 6 },
                                           DumpLogValues{ cpt::log::Level::Debug, 5 },
                                           DumpLogValues{ cpt::log::Level::Info, 4 },
                                           DumpLogValues{ cpt::log::Level::Warn, 3 },
                                           DumpLogValues{ cpt::log::Level::Error, 2 },
                                           DumpLogValues{ cpt::log::Level::Critical, 1 },
                                           DumpLogValues{ cpt::log::Level::None, 0 }));

TEST(LOG, CLEAR) {
    cpt::log::clear();
    cpt::log::set_level(cpt::log::Level::Info);

    cpt::log::r_info("message");
    auto const dump = cpt::log::dump(cpt::log::Level::Info);
    EXPECT_FALSE(dump.empty());

    cpt::log::clear();
    auto const dump_2 = cpt::log::dump(cpt::log::Level::Info);
    EXPECT_TRUE(dump_2.empty());
}


TEST(LOG, SAVE) {
    cpt::log::clear();
    cpt::log::set_level(cpt::log::Level::Info);

    cpt::log::r_info("message\nmessage\nmessage");
    cpt::log::r_warn("message");
    cpt::log::r_critical("message");

    auto const path   = std::filesystem::temp_directory_path() / "cpt_log_test.txt";
    auto const result = cpt::log::save(cpt::log::Level::Info, path);

    EXPECT_TRUE(result.has_value());
}
