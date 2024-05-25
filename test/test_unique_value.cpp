//
// Purpur Tentakel
// cpp 23
// 25.05.24
//

#include <cpt/unique_value.hpp>
#include <gtest/gtest.h>

template<typename T>
struct Counter final {
    int* counter;

    constexpr void operator()(T const&) {
        ++*counter;
    }
};

struct Callable final {
    void call() const { }
    void call() { }
};

TEST(UniqueValue, Construct) {
    [[maybe_unused]] auto constexpr test = cpt::UniqueValue{ 6 };
}

TEST(UniqueValue, ConstructWithDeleter) {
    int counter = 0;

    {
        [[maybe_unused]] auto const test = cpt::UniqueValue{ 6, Counter<int>(&counter) };
        EXPECT_EQ(counter, 0);
    }

    EXPECT_EQ(counter, 1);
}

TEST(UniqueValue, CopyConstructable) {
    static_assert(not std::copyable<cpt::UniqueValue<int>>);
    static_assert(not std::copy_constructible<cpt::UniqueValue<int>>);
    static_assert(not std::is_copy_assignable_v<cpt::UniqueValue<int>>);
}

TEST(UniqueValue, MoveConstructer) {
    static_assert(std::movable<cpt::UniqueValue<int>>);

    int counter = 0;
    {
        auto test   = cpt::UniqueValue{ 6, Counter<int>(&counter) };
        auto test_2 = std::move(test);

        EXPECT_FALSE(test.has_value());
        EXPECT_TRUE(test_2.has_value());

        EXPECT_EQ(test_2.value(), 6);

        EXPECT_EQ(counter, 0);
    }
    EXPECT_EQ(counter, 1);
}

TEST(UniqueValue, MoveAssignment) {
    static_assert(std::movable<cpt::UniqueValue<int>>);

    int counter = 0;
    {
        auto test   = cpt::UniqueValue{ 6, Counter<int>(&counter) };
        auto test_2 = cpt::UniqueValue{ 10, Counter<int>(&counter) };

        EXPECT_EQ(counter, 0);
        test = std::move(test_2);
        EXPECT_EQ(counter, 1);

        EXPECT_TRUE(test.has_value());
        EXPECT_FALSE(test_2.has_value());

        EXPECT_EQ(test.value(), 10);

        EXPECT_EQ(counter, 1);
    }
    EXPECT_EQ(counter, 2);
}

auto self_assignment(auto& lhs, auto& rhs) {
    lhs = std::move(rhs);
}

TEST(UniqueValue, SelfAssignment) {
    int counter = 0;


    {
        auto test = cpt::UniqueValue{ 6, Counter<int>(&counter) };
        self_assignment(test, test);

        EXPECT_TRUE(test.has_value());

        EXPECT_EQ(test.value(), 6);
        EXPECT_EQ(counter, 0);
    }
    EXPECT_EQ(counter, 1);
}

TEST(UniqueValue, Value) {
    auto test             = cpt::UniqueValue{ 6 };
    auto constexpr test_2 = cpt::UniqueValue{ 6 };

    [[maybe_unused]] auto const value   = test.value();
    [[maybe_unused]] auto const value_2 = test_2.value();

    EXPECT_EQ(value, 6);
    EXPECT_EQ(value_2, 6);
}

TEST(UniqueValue, Operator) {
    auto constexpr test_const = cpt::UniqueValue{ 6 };

    auto const cast_const  = static_cast<int>(test_const);
    auto const deref_const = *test_const;
    EXPECT_EQ(cast_const, 6);
    EXPECT_EQ(deref_const, 6);

    auto test        = cpt::UniqueValue{ 6 };
    auto const cast  = static_cast<int>(test);
    auto const deref = *test;
    EXPECT_EQ(cast, 6);
    EXPECT_EQ(deref, 6);


    auto constexpr test_call_const = cpt::UniqueValue{ Callable{} };
    test_call_const->call();

    auto test_call = cpt::UniqueValue{ Callable{} };
    test_call->call();
}

TEST(UniqueValue, ThrowEmptyValue) {
    auto test = cpt::UniqueValue{ 6 };

    auto test_2 = std::move(test);
    EXPECT_THROW([[maybe_unused]] auto bla = test.value(), tl::bad_optional_access);

    auto const test_3 = std::move(test);
    EXPECT_THROW([[maybe_unused]] auto bla = test_3.value(), tl::bad_optional_access);
}

TEST(UniqueValue, ThrowEmptyT) {
    auto test = cpt::UniqueValue{ 6 };

    auto test_2 = std::move(test);
    EXPECT_THROW([[maybe_unused]] auto bla = static_cast<int>(test), tl::bad_optional_access);

    auto const test_3 = std::move(test);
    EXPECT_THROW([[maybe_unused]] auto bla = static_cast<int>(test_3), tl::bad_optional_access);
}

TEST(UniqueValue, ThrowEmptyStar) {
    auto test = cpt::UniqueValue{ 6 };

    auto test_2 = std::move(test);
    EXPECT_THROW([[maybe_unused]] auto bla = *test, tl::bad_optional_access);

    auto const test_3 = std::move(test);
    EXPECT_THROW([[maybe_unused]] auto bla = *test_3, tl::bad_optional_access);
}

TEST(UniqueValue, ThrowEmptyArrow) {
    auto test = cpt::UniqueValue{ Callable{} };

    auto test_2 = std::move(test);
    EXPECT_THROW(test->call(), tl::bad_optional_access);

    auto const test_3 = std::move(test);
    EXPECT_THROW(test_3->call(), tl::bad_optional_access);
}
