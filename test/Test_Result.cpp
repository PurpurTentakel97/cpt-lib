//
// Purpur Tentakel
// cpp 23
// 11.05.24
//

#include <cpt/Result.hpp>
#include <gtest/gtest.h>

enum class Error {
    default_error,
};

enum class Result {
    default_result,
    other_result,
};

TEST(Result, Construct_Result) {
    auto const result = cpt::Result<Result, Error>(Result::default_result);

    auto const test_exception = [result]() {
        try {
            [[maybe_unused]] auto const r = result.unwrap_err();
        } catch (std::logic_error const& e) {
            EXPECT_STREQ(e.what(), "while unwrapping an result with 'unwrap_err'");
            throw;
        }
    };

    ASSERT_TRUE(result.ok());
    ASSERT_FALSE(result.err());
    ASSERT_EQ(result.unwrap(), Result::default_result);
    ASSERT_THROW(test_exception(), std::logic_error);
    ASSERT_EQ(result.unwrap_or(Result::other_result), Result::default_result);
}

TEST(Result, Construct_Error) {
    auto const result = cpt::Result<Result, Error>(Error::default_error);

    auto const test_exception = [result]() {
        try {
            [[maybe_unused]] auto const r = result.unwrap();
        } catch (std::logic_error const& e) {
            EXPECT_STREQ(e.what(), "while unwrapping a result with 'unwarp'");
            throw;
        }
    };

    ASSERT_TRUE(result.err());
    ASSERT_FALSE(result.ok());
    ASSERT_EQ(result.unwrap_err(), Error::default_error);
    ASSERT_THROW(test_exception(), std::logic_error);
    ASSERT_EQ(result.unwrap_or(Result::default_result), Result::default_result);
}
