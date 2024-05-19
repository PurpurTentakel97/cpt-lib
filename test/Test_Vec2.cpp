//
// Purpur Tentakel
// cpp 23
// 19.05.24
//

#include <cmath>
#include <cpt/Vec2.hpp>
#include <gtest/gtest.h>

TEST(Vec2, OperatorAddAssign) {
    auto vec_1           = cpt::Vec2i{ 1, 2 };
    auto constexpr vec_2 = cpt::Vec2i{ 3, 4 };
    vec_1 += vec_2;

    EXPECT_EQ(vec_1.x, 4);
    EXPECT_EQ(vec_1.y, 6);
}

TEST(Vec2, OperatorMinusAssign) {
    auto vec_1           = cpt::Vec2i{ 10, 2 };
    auto constexpr vec_2 = cpt::Vec2i{ 3, 4 };
    vec_1 -= vec_2;

    EXPECT_EQ(vec_1.x, 7);
    EXPECT_EQ(vec_1.y, -2);
}

TEST(Vec2, OperatorMultiplyAssign) {
    auto vec              = cpt::Vec2i{ 2, 3 };
    auto constexpr scalar = 2;
    vec *= scalar;

    EXPECT_EQ(vec.x, 4);
    EXPECT_EQ(vec.y, 6);
}

TEST(Vec2, OperatorDivideAssign) {
    auto vec                = cpt::Vec2i{ 4, 6 };
    auto constexpr scalar_1 = 0;
    auto constexpr scalar_2 = 2;

    try {
        vec /= scalar_1;
        GTEST_FAIL() << "exception 'BadVec2Argument' not thrown";
    } catch (cpt::BadVec2Argument const& e) {
        EXPECT_STREQ(e.what(), "devision by 0");
        EXPECT_EQ(vec.x, 4);
        EXPECT_EQ(vec.y, 6);
    }

    vec /= scalar_2;
    EXPECT_EQ(vec.x, 2);
    EXPECT_EQ(vec.y, 3);
}

TEST(Vec2, OperatorPlus) {
    auto constexpr vec_1 = cpt::Vec2i{ 1, 2 };
    auto constexpr vec_2 = cpt::Vec2i{ 3, 4 };
    auto constexpr vec_3 = vec_1 + vec_2;

    EXPECT_EQ(vec_3.x, 4);
    EXPECT_EQ(vec_3.y, 6);
}

TEST(Vec2, OperatorMinus) {
    auto constexpr vec_1 = cpt::Vec2i{ 10, 2 };
    auto constexpr vec_2 = cpt::Vec2i{ 3, 4 };
    auto constexpr vec_3 = vec_1 - vec_2;

    EXPECT_EQ(vec_3.x, 7);
    EXPECT_EQ(vec_3.y, -2);
}

TEST(Vec2, OperatorMultiply) {
    auto constexpr vec    = cpt::Vec2i{ 2, 3 };
    auto constexpr scalar = 2;
    auto constexpr vec_2  = vec * scalar;
    auto constexpr vec_3  = scalar * vec;

    EXPECT_EQ(vec_2.x, 4);
    EXPECT_EQ(vec_2.y, 6);
    EXPECT_EQ(vec_3.x, 4);
    EXPECT_EQ(vec_3.y, 6);
}

TEST(Vec2, OperatorDivide) {
    auto constexpr vec      = cpt::Vec2i{ 4, 6 };
    auto constexpr scalar_1 = 0;
    auto constexpr scalar_2 = 2;

    try {
        auto const vec_2 = vec / scalar_1;
        GTEST_FAIL() << "exception 'BadVec2Argument' not thrown";
    } catch (cpt::BadVec2Argument const& e) { EXPECT_STREQ(e.what(), "devision by 0"); }

    auto constexpr vec_3 = vec / scalar_2;
    EXPECT_EQ(vec_3.x, 2);
    EXPECT_EQ(vec_3.y, 3);
}

TEST(Vec2, OperatorSpaceship) {
    auto constexpr vec_1 = cpt::Vec2i(1, 4);
    auto constexpr vec_2 = cpt::Vec2i(2, 3);

    EXPECT_TRUE(vec_1 == vec_1);

    EXPECT_TRUE(vec_1 != vec_2);

    EXPECT_TRUE(vec_1 <= vec_2);
    EXPECT_TRUE(vec_1 <= vec_1);

    EXPECT_TRUE(vec_2 >= vec_1);
    EXPECT_TRUE(vec_1 >= vec_1);

    EXPECT_TRUE(vec_1 < vec_2);
    EXPECT_TRUE(vec_2 > vec_1);
}

TEST(Vec2, Magnetude) {
    EXPECT_DOUBLE_EQ(cpt::Vec2i(1, 1).magnitude(), std::sqrt(2));
    EXPECT_DOUBLE_EQ(cpt::Vec2i(2, 2).magnitude(), std::sqrt(8));
    EXPECT_DOUBLE_EQ(cpt::Vec2i(1, 2).magnitude(), std::sqrt(5));
}

TEST(Vec2, Normalize) {
    EXPECT_DOUBLE_EQ(cpt::Vec2i(1, 1).normalize().magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(cpt::Vec2i(2, 10).normalize().magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(cpt::Vec2i(-20, 50).normalize().magnitude(), 1.0);
}

TEST(Vec2, ToUnchecked) {
    auto constexpr vec   = cpt::Vec2i(20, 20);
    auto constexpr vec_2 = vec.to_unchecked<float>();
    auto constexpr vec_3 = vec.to_unchecked<cpt::usize>();
}

TEST(Vec2, To) {
    auto constexpr max = std::numeric_limits<double>::max();
    auto constexpr vec = cpt::Vec2d(max, max);

    try {
        auto const vec_test = vec.to<float>();
        GTEST_FAIL() << "Expection 'BadVec2Convertion' not thrown";
    } catch (cpt::BadVec2Convertion const& e) {
        EXPECT_STREQ(e.what(), "not able to convert values into new datatype");
    }

    auto constexpr max_2 = std::numeric_limits<cpt::i64>::max();
    auto constexpr vec_2 = cpt::Vec2i64(max_2, max_2);

    try {
        auto const vec_test = vec.to<cpt::i8>();
        GTEST_FAIL() << "Expection 'BadVec2Convertion' not thrown";
    } catch (cpt::BadVec2Convertion const& e) {
        EXPECT_STREQ(e.what(), "not able to convert values into new datatype");
    }
}
