//
// Purpur Tentakel
// cpp 23
// 11.05.24
//

#include <cpt/Result.hpp>
#include <gtest/gtest.h>

enum class Error {
    default_error,
    other_error,
};

class Value {
private:
    int m_value;

public:
    explicit Value(int value) : m_value{ value } { }
    Value() = default;

    [[nodiscard]] int value() const {
        return m_value;
    }

    friend bool operator==(Value const& lhs, Value const& rhs);
};

bool operator==(Value const& lhs, Value const& rhs) {
    return lhs.m_value == rhs.m_value;
}


TEST(Result, OK) {
    auto const result = cpt::Result<Value, Error>(Value(1));

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
    ASSERT_EQ(result.unwrap(), Value(1));
    ASSERT_THROW(test_exception(), std::logic_error);
    ASSERT_EQ(result.unwrap_or(Value(2)), Value(1));
    ASSERT_EQ(result.unwarp_or_else([]() { return Value(2); }), Value(1));
    ASSERT_EQ(result.unwrap_or_default(), Value(1));
}

TEST(Result, Error) {
    auto const result = cpt::Result<Value, Error>(cpt::Err(Error::default_error));

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
    ASSERT_EQ(result.unwrap_or(Value(2)), Value(2));
    ASSERT_EQ(result.unwarp_or_else([]() { return Value(2); }), Value(2));
    ASSERT_EQ(result.unwrap_or_default(), Value(0));
}

TEST(Result, OK_Same_Type) {
    auto const result         = cpt::Result<Value, Value>(Value(1));
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
    ASSERT_EQ(result.unwrap(), Value(1));
    ASSERT_THROW(test_exception(), std::logic_error);
    ASSERT_EQ(result.unwrap_or(Value(2)), Value(1));
    ASSERT_EQ(result.unwarp_or_else([]() { return Value(2); }), Value(1));
    ASSERT_EQ(result.unwrap_or_default(), Value(1));
}

TEST(Result, Error_Same_Type) {
    auto const result = cpt::Result<Error, Error>(cpt::Err(Error::default_error));

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
    ASSERT_EQ(result.unwrap_or(Error::other_error), Error::other_error);
    ASSERT_EQ(result.unwarp_or_else([](){return Error::other_error;}), Error::other_error);
    ASSERT_EQ(result.unwrap_or_default(), Error::default_error);
}
