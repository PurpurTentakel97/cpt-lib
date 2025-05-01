//
// Purpur Tentakel
// 19.05.24
//

#include <cmath>
#include <cpt/vec2.hpp>
#include <gtest/gtest.h>

TEST(Vec2, OperatorAddAssign) {
    auto vec_1           = cpt::Vec2_i{ 1, 2 };
    auto constexpr vec_2 = cpt::Vec2_i{ 3, 4 };
    vec_1 += vec_2;

    EXPECT_EQ(vec_1.x, 4) << "unexpected x after AddAssign.\nexpected: 4\nprovided: " << vec_1.x;
    EXPECT_EQ(vec_1.y, 6) << "unexpected y after AddAssign.\nexpected: 6\nprovided: " << vec_1.y;
}

TEST(Vec2, OperatorMinusAssign) {
    auto vec_1           = cpt::Vec2_i{ 10, 2 };
    auto constexpr vec_2 = cpt::Vec2_i{ 3, 4 };
    vec_1 -= vec_2;

    EXPECT_EQ(vec_1.x, 7) << "unexpected x after MunisAssign.\nexpected: 7\nprovided: " << vec_1.x;
    EXPECT_EQ(vec_1.y, -2) << "unexpected y after MunisAssign.\nexpected: -2\nprovided: " << vec_1.y;
}

TEST(Vec2, OperatorMultiplyAssign) {
    auto vec              = cpt::Vec2_i{ 2, 3 };
    auto constexpr scalar = 2;
    vec *= scalar;

    EXPECT_EQ(vec.x, 4) << "unexpected x after MultiplyAssign.\nexpected: 4\nprovided: " << vec.x;
    EXPECT_EQ(vec.y, 6) << "unexpected y after MultiplyAssign.\nexpected: 6\nprovided: " << vec.y;
}

TEST(Vec2, OperatorDivideAssign) {
    auto vec                = cpt::Vec2_i{ 4, 6 };
    auto constexpr scalar_1 = 0;
    auto constexpr scalar_2 = 2;

    try {
        vec /= scalar_1;
        GTEST_FAIL() << "exception 'BadVec2Argument' not thrown after DivideAssign with 0";
    } catch (cpt::BadVec2Argument const& e) {
        EXPECT_STREQ(e.what(), "division by 0")
                << "unexpected error message after divide by 0.\nexpected: 'division by 0'\nprovided: " << e.what();
        EXPECT_EQ(vec.x, 4) << "unexpected x after DivideAssign after divide by 0.\nexpected: 4\nprovided: " << vec.x;
        EXPECT_EQ(vec.y, 6) << "unexpected y after DivideAssign after divide by 0.\nexpected: 6\nprovided: " << vec.y;
    }

    vec /= scalar_2;
    EXPECT_EQ(vec.x, 2) << "unexpected x after DivideAssign (no exception).\nexpected: 2\nprovided: " << vec.x;
    EXPECT_EQ(vec.y, 3) << "unexpected y after DivideAssign (no exception).\nexpected: 3\nprovided: " << vec.y;
    ;
}

TEST(Vec2, OperatorPlus) {
    auto constexpr vec_1 = cpt::Vec2_i{ 1, 2 };
    auto constexpr vec_2 = cpt::Vec2_i{ 3, 4 };
    auto constexpr vec_3 = vec_1 + vec_2;

    EXPECT_EQ(vec_3.x, 4) << "unexpected x after OperatorPlus.\nexpected: 4\nprovided: " << vec_3.x;
    EXPECT_EQ(vec_3.y, 6) << "unexpected y after OperatorPlus.\nexpected: 6\nprovided: " << vec_3.y;
}

TEST(Vec2, OperatorMinus) {
    auto constexpr vec_1 = cpt::Vec2_i{ 10, 2 };
    auto constexpr vec_2 = cpt::Vec2_i{ 3, 4 };
    auto constexpr vec_3 = vec_1 - vec_2;

    EXPECT_EQ(vec_3.x, 7) << "unexpected x after OperatorMinus.\nexpected: 7\nprovided: " << vec_3.x;
    EXPECT_EQ(vec_3.y, -2) << "unexpected y after OperatorMinus.\nexpected: -2\nprovided: " << vec_3.y;
}

TEST(Vec2, OperatorMultiply) {
    auto constexpr vec    = cpt::Vec2_i{ 2, 3 };
    auto constexpr scalar = 2;
    auto constexpr vec_2  = vec * scalar;
    auto constexpr vec_3  = scalar * vec;

    EXPECT_EQ(vec_2.x, 4) << "unexpected x after OperatorMultiply with scalar right.\nexpected: 4\nprovided: "
                          << vec_2.x;
    EXPECT_EQ(vec_2.y, 6) << "unexpected y after OperatorMultiply with scalar right.\nexpected: 6\nprovided: "
                          << vec_2.y;
    EXPECT_EQ(vec_3.x, 4) << "unexpected x after OperatorMultiply with scalar left.\nexpected: 4\nprovided: "
                          << vec_3.x;
    EXPECT_EQ(vec_3.y, 6) << "unexpected y after OperatorMultiply with scalar left.\nexpected: 6\nprovided: "
                          << vec_3.y;
}

TEST(Vec2, OperatorDivide) {
    auto constexpr vec      = cpt::Vec2_i{ 4, 6 };
    auto constexpr scalar_1 = 0;
    auto constexpr scalar_2 = 2;

    try {
        [[maybe_unused]] auto const vec_2 = vec / scalar_1;
        GTEST_FAIL() << "exception 'BadVec2Argument' not thrown after debide by 0";
    } catch (cpt::BadVec2Argument const& e) { EXPECT_STREQ(e.what(), "division by 0"); }

    auto constexpr vec_3 = vec / scalar_2;
    EXPECT_EQ(vec_3.x, 2) << "unexpected x after OperatorDivide.\nexpected: 2\nprovided: " << vec_3.x;
    EXPECT_EQ(vec_3.y, 3) << "unexpected y after OperatorDivide.\nexpected: 3\nprovided: " << vec_3.y;
}

TEST(Vec2, OperatorSpaceship) {
    auto constexpr vec_1 = cpt::Vec2_i(1, 4);
    auto constexpr vec_2 = cpt::Vec2_i(2, 3);

    EXPECT_TRUE(vec_1 == vec_1);

    EXPECT_TRUE(vec_1 != vec_2);

    EXPECT_TRUE(vec_1 <= vec_2);
    EXPECT_TRUE(vec_1 <= vec_1);

    EXPECT_TRUE(vec_2 >= vec_1);
    EXPECT_TRUE(vec_1 >= vec_1);

    EXPECT_TRUE(vec_1 < vec_2);
    EXPECT_TRUE(vec_2 > vec_1);
}

TEST(Vec2, Magnitude) {
    auto const value_1    = cpt::Vec2_i(1, 1).magnitude();
    auto const expected_1 = std::sqrt(2);
    EXPECT_DOUBLE_EQ(value_1, expected_1)
            << "unexpected length after magnitude.\nexpected: " << expected_1 << "\n provided: " << value_1;
    auto const value_2    = cpt::Vec2_i(2, 2).magnitude();
    auto const expected_2 = std::sqrt(8);
    EXPECT_DOUBLE_EQ(value_2, expected_2)
            << "unexpected length after magnitude.\nexpected: " << expected_2 << "\n provided: " << value_2;
    auto const value_3    = cpt::Vec2_i(1, 2).magnitude();
    auto const expected_3 = std::sqrt(5);
    EXPECT_DOUBLE_EQ(value_3, expected_3)
            << "unexpected length after magnitude.\nexpected: " << expected_3 << "\n provided: " << value_3;
}

TEST(Vec2, Normalize) {
    auto const value_1 = cpt::Vec2_i(1, 1).normalize().magnitude();
    EXPECT_DOUBLE_EQ(value_1, 1.0) << "unexpected length after normalize.\nexpected: 1.0\n provided: " << value_1;
    auto const value_2 = cpt::Vec2_i(2, 10).normalize().magnitude();
    EXPECT_DOUBLE_EQ(value_2, 1.0) << "unexpected length after normalize.\nexpected: 1.0\n provided: " << value_2;
    auto const value_3 = cpt::Vec2_i(-20, 50).normalize().magnitude();
    EXPECT_DOUBLE_EQ(value_3, 1.0) << "unexpected length after normalize.\nexpected: 1.0\n provided: " << value_3;
}

TEST(Vec2, To) {
    auto constexpr vec                    = cpt::Vec2_i(20, 20);
    [[maybe_unused]] auto constexpr vec_2 = vec.to<float>();
    [[maybe_unused]] auto constexpr vec_3 = vec.to<cpt::usize>();
}
