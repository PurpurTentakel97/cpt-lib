//
// Purpur Tentakel
// cpp 23
// 05.05.24
//

#include <gtest/gtest.h>
#include <cpt/Strings.hpp>
#include <string>
#include <tuple>

class StriptStringFictures : public testing::TestWithParam<std::tuple<std::string, std::string, std::string, std::string>>
{
};

TEST_P(StriptStringFictures, TRIM)
{
    auto input = std::get<0>(GetParam());
    auto const output = std::get<1>(GetParam());
    cpt::trim(input);
    EXPECT_EQ(input, output);
}

TEST_P(StriptStringFictures, LTRIM)
{
    auto input = std::get<0>(GetParam());
    auto const output = std::get<2>(GetParam());
    cpt::ltrim(input);
    EXPECT_EQ(input, output);
}

TEST_P(StriptStringFictures, RTRIM)
{
    auto input = std::get<0>(GetParam());
    auto const output = std::get<3>(GetParam());
    cpt::rtrim(input);
    EXPECT_EQ(input, output);
}

TEST_P(StriptStringFictures, TRIM_COPY)
{
    auto const input = std::get<0>(GetParam());
    auto const output = std::get<1>(GetParam());
    auto const result = cpt::trim_copy(input);
    EXPECT_EQ(result, output);
    EXPECT_EQ(std::get<0>(GetParam()), input);
}

TEST_P(StriptStringFictures, LTRIM_COPY)
{
    auto const input = std::get<0>(GetParam());
    auto const output = std::get<2>(GetParam());
    auto const result = cpt::ltrim_copy(input);
    EXPECT_EQ(result, output);
    EXPECT_EQ(std::get<0>(GetParam()), input);
}

TEST_P(StriptStringFictures, RTRIM_COPY)
{
    auto const input = std::get<0>(GetParam());
    auto const output = std::get<3>(GetParam());
    auto const result = cpt::rtrim_copy(input);
    EXPECT_EQ(result, output);
    EXPECT_EQ(std::get<0>(GetParam()), input);
}

INSTANTIATE_TEST_SUITE_P(
    STRINGS,
    StriptStringFictures,
    ::testing::Values(
        /*
         * the input in defined as followed
         * 0 : input
         * 1 : trim output
         * 2 : ltrim output
         * 3 : rtrim output
         */
        std::make_tuple("    test     ", "test", "test     ", "    test"),
        std::make_tuple("      test", "test", "test", "      test"),
        std::make_tuple("test     ", "test", "test     ","test"),
        std::make_tuple("    test    test    ", "test    test", "test    test    ", "    test    test"),
        std::make_tuple("\ntest", "test", "test", "\ntest"),
        std::make_tuple("test\n", "test", "test\n", "test"),
        std::make_tuple("\ttest", "test", "test", "\ttest"),
        std::make_tuple("test\t", "test", "test\t", "test")
        ));
