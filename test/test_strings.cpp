//
// Purpur Tentakel
// 05.05.24
//

#include <cpt/strings.hpp>
#include <gtest/gtest.h>
#include <tuple>

class TrimStringFictures
    : public testing::TestWithParam<std::tuple<std::string, std::string, std::string, std::string>> { };

TEST_P(TrimStringFictures, TRIM) {
    auto input        = std::get<0>(GetParam());
    auto const output = std::get<1>(GetParam());
    cpt::trim(input);
    EXPECT_EQ(input, output) << "unexpected result while trim:\nexpected: '" << output << "'\nprovided: '" << input
                             << "'";
}

TEST_P(TrimStringFictures, LTRIM) {
    auto input        = std::get<0>(GetParam());
    auto const output = std::get<2>(GetParam());
    cpt::ltrim(input);
    EXPECT_EQ(input, output) << "unexpected result while ltrim:\nexpected: '" << output << "'\nprovided: '" << input
                             << "'";
}

TEST_P(TrimStringFictures, RTRIM) {
    auto input        = std::get<0>(GetParam());
    auto const output = std::get<3>(GetParam());
    cpt::rtrim(input);
    EXPECT_EQ(input, output) << "unexpected result while rtrim:\nexpected: '" << output << "'\nprovided: '" << input
                             << "'";
}

TEST_P(TrimStringFictures, TRIM_COPY) {
    auto const input  = std::get<0>(GetParam());
    auto const output = std::get<1>(GetParam());
    auto const result = cpt::trim_copy(input);
    EXPECT_EQ(result, output) << "unexpected result while copy_trim:\nexpected: '" << output << "'\nprovided: '"
                              << input << "'";
    EXPECT_EQ(std::get<0>(GetParam()), input) << "input was changed while trim_copy";
}

TEST_P(TrimStringFictures, LTRIM_COPY) {
    auto const input  = std::get<0>(GetParam());
    auto const output = std::get<2>(GetParam());
    auto const result = cpt::ltrim_copy(input);
    EXPECT_EQ(result, output) << "unexpected result while lcopy_trim:\nexpected: '" << output << "'\nprovided: '"
                              << input << "'";
    EXPECT_EQ(std::get<0>(GetParam()), input) << "input was changed while ltrim_copy";
}

TEST_P(TrimStringFictures, RTRIM_COPY) {
    auto const input  = std::get<0>(GetParam());
    auto const output = std::get<3>(GetParam());
    auto const result = cpt::rtrim_copy(input);
    EXPECT_EQ(result, output) << "unexpected result while rcopy_trim:\nexpected: '" << output << "'\nprovided: '"
                              << input << "'";
    EXPECT_EQ(std::get<0>(GetParam()), input) << "input was changed while rtrim_copy";
}

INSTANTIATE_TEST_SUITE_P(
        STRINGS,
        TrimStringFictures,
        ::testing::Values(
                /*
         * the input in defined as followed
         * 0 : input
         * 1 : trim output
         * 2 : ltrim output
         * 3 : rtrim output
         */
                std::make_tuple("    test     ", "test", "test     ", "    test"), // whitespace front & back
                std::make_tuple("      test", "test", "test", "      test"),       // whitespace front
                std::make_tuple("test     ", "test", "test     ", "test"),         // whitespace back
                std::make_tuple("    test    test    ", "test    test", "test    test    ", "    test    test"),
                // whitespace front, mid & back
                std::make_tuple("\ntest", "test", "test", "\ntest"), // newline front
                std::make_tuple("test\n", "test", "test\n", "test"), // newline back
                std::make_tuple("\ttest", "test", "test", "\ttest"), // tab front
                std::make_tuple("test\t", "test", "test\t", "test")  // tab back
                ));


class SplitStringFictures
    : public testing::TestWithParam<
              std::tuple<std::string, std::string, cpt::SplitBehavior, std::vector<std::string>>> { };

TEST_P(SplitStringFictures, SPLIT) {
    auto const input         = std::get<0>(GetParam());
    auto const delimiter     = std::get<1>(GetParam());
    auto const empty_entries = std::get<2>(GetParam());
    auto const output        = std::get<3>(GetParam());
    auto const result        = cpt::split(input, delimiter, empty_entries);

    EXPECT_EQ(output.size(), result.size())
            << "unexpect split count:\nexpected: " << output.size() << "\nprovided: " << result.size();
    for (std::size_t i = 0; i < output.size(); ++i) {
        EXPECT_EQ(result[i], output[i]) << "unexpected line after splitting:\nexpected: 1" << output[i]
                                        << "\nprovided: " << result[i];
    }
    EXPECT_EQ(std::get<0>(GetParam()), input) << "input has changes after splitting";
}

INSTANTIATE_TEST_SUITE_P(STRINGS,
                         SplitStringFictures,
                         testing::Values(
                                 // simple delimiter test, skip
                                 std::make_tuple("test\ntest\ntest",
                                                 "\n",
                                                 cpt::SplitBehavior::SkipEmptyParts,
                                                 std::vector<std::string>{ "test", "test", "test" }),
                                 // simple delimiter test, keep
                                 std::make_tuple("test\ntest\ntest",
                                                 "\n",
                                                 cpt::SplitBehavior::KeepEmptyParts,
                                                 std::vector<std::string>{ "test", "test", "test" }),
                                 // delimiter front, skip
                                 std::make_tuple("\ntest\ntest",
                                                 "\n",
                                                 cpt::SplitBehavior::SkipEmptyParts,
                                                 std::vector<std::string>{ "test", "test" }),
                                 // delimiter front, keep
                                 std::make_tuple("\ntest\ntest",
                                                 "\n",
                                                 cpt::SplitBehavior::KeepEmptyParts,
                                                 std::vector<std::string>{ "", "test", "test" }),
                                 // delimiter back, skip
                                 std::make_tuple("test\ntest\n",
                                                 "\n",
                                                 cpt::SplitBehavior::SkipEmptyParts,
                                                 std::vector<std::string>{ "test", "test" }),
                                 // delimiter back, kepp
                                 std::make_tuple("test\ntest\n",
                                                 "\n",
                                                 cpt::SplitBehavior::KeepEmptyParts,
                                                 std::vector<std::string>{ "test", "test", "" }),
                                 // double delimiter, skip
                                 std::make_tuple("test\n\ntest\ntest",
                                                 "\n",
                                                 cpt::SplitBehavior::SkipEmptyParts,
                                                 std::vector<std::string>{ "test", "test", "test" }),
                                 // double delimiter, skip
                                 std::make_tuple("test\n\ntest\ntest",
                                                 "\n",
                                                 cpt::SplitBehavior::KeepEmptyParts,
                                                 std::vector<std::string>{ "test", "", "test", "test" }),
                                 // multiple delimiter test, skip
                                 std::make_tuple("test, test, test",
                                                 ", ",
                                                 cpt::SplitBehavior::SkipEmptyParts,
                                                 std::vector<std::string>{ "test", "test", "test" }),
                                 // multiple delimiter test, keep
                                 std::make_tuple("test, test, test",
                                                 ", ",
                                                 cpt::SplitBehavior::KeepEmptyParts,
                                                 std::vector<std::string>{ "test", "test", "test" }),
                                 // multiple delimiter all, skip
                                 std::make_tuple(", test, , test, test, ",
                                                 ", ",
                                                 cpt::SplitBehavior::SkipEmptyParts,
                                                 std::vector<std::string>{ "test", "test", "test" }),
                                 // multiple delimiter all, keep
                                 std::make_tuple(", test, , test, test, ",
                                                 ", ",
                                                 cpt::SplitBehavior::KeepEmptyParts,
                                                 std::vector<std::string>{ "", "test", "", "test", "test", "" })));


struct ReplaceValues final {
    std::string str;
    std::string old;
    std::string new_;
    std::string expected;
};

class Replace : public testing::TestWithParam<ReplaceValues> { };

TEST_P(Replace, REPLACE) {
    auto params = GetParam();

    cpt::replace(params.str, params.old, params.new_);
    EXPECT_EQ(params.str, params.expected) << "unexpected replacement\nold: " << params.old << "\nnew: " << params.new_
                                           << "\nexpected: " << params.expected << "\nprovided: " << params.str;
}

INSTANTIATE_TEST_SUITE_P(REPLACE,
                         Replace,
                         testing::Values(ReplaceValues{ "123456", "456", "123", "123123" },
                                         ReplaceValues{ "123456", "123", "456", "456456" },
                                         ReplaceValues{ "123123", "123", "456", "456456" },
                                         ReplaceValues{ "123123", "1231", "4564", "456423" } ,
                                         ReplaceValues{ "123456", "1", "2", "223456" },
                                         ReplaceValues{ "123456", "123", "123456", "123456456" },
                                         ReplaceValues{ "123456", "23456", "12", "112" }));
