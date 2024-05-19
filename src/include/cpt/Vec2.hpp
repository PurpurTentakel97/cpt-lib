//
// Purpur Tentakel
// cpp 23
// 19.05.24
//

#pragma once

#include <cmath>
#include <cpt/Concepts.hpp>
#include <cpt/Types.hpp>
#include <stdexcept>

namespace cpt {
    class BadVec2Convertion final : public std::out_of_range {
        using std::out_of_range::out_of_range;
    };
    class BadVec2Argument final : public std::invalid_argument {
        using std::invalid_argument::invalid_argument;
    };

    template<IsNumeric T>
    struct Vec2 final {
        T x{};
        T y{};

        constexpr Vec2() = default;
        constexpr Vec2(T const x_, T const y_) : x{ x_ }, y{ y_ } { }

        template<IsNumeric U>
        [[nodiscard]] constexpr Vec2<U> to() const {
            auto is_in_range{ false };
            if constexpr (std::integral<T> and std::integral<U>) {
                is_in_range = std::in_range<U>(x) and std::in_range<U>(y);
            } else if constexpr (std::unsigned_integral<U>) {
                auto constexpr max = std::numeric_limits<U>::max();
                auto constexpr min = std::numeric_limits<U>::min();
                // clang-format off
                is_in_range = x >= min
                           && x <= max
                           && y >= min
                           && y <= max;
                // clang-format on
            } else {
                auto constexpr max = std::numeric_limits<U>::max();
                auto constexpr min = -max;
                // clang-format off
                is_in_range = x >= min
                           && x <= max
                           && y >= min
                           && y <= max;
                // clang-format on
            }

            if (not is_in_range) {
                throw BadVec2Convertion("not able to convert values into new datatype");
            }

            return to_unchecked<U>();
        }

        template<IsNumeric U>
        [[nodiscard]] constexpr Vec2<U> to_unchecked() const {
            return { static_cast<U>(x), static_cast<U>(y) };
        }

        constexpr Vec2& operator+=(Vec2 const& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Vec2& operator-=(Vec2 const& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr Vec2& operator*=(T const& scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        constexpr Vec2& operator/=(T const& scalar) {
            if (scalar == T{}) {
                throw BadVec2Argument("devision by 0");
            }
            x /= scalar;
            y /= scalar;
            return *this;
        }

        [[nodiscard]] friend constexpr Vec2 operator+(Vec2 lhs, Vec2 const rhs) {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] friend constexpr Vec2 operator-(Vec2 lhs, Vec2 const rhs) {
            lhs -= rhs;
            return lhs;
        }

        [[nodiscard]] friend constexpr Vec2 operator*(Vec2 lhs, T const rhs) {
            lhs *= rhs;
            return lhs;
        }
        [[nodiscard]] friend constexpr Vec2 operator*(T const lhs, Vec2 rhs) {
            return rhs * lhs;
        }

        [[nodiscard]] friend constexpr Vec2 operator/(Vec2 lhs, T const rhs) {
            lhs /= rhs;
            return lhs;
        }

        [[nodiscard]] friend constexpr auto operator<=>(Vec2 const& lhs, Vec2 const& rhs) = default;

        [[nodiscard]] constexpr double magnitude() const {
            auto const x_ = static_cast<double>(x);
            auto const y_ = static_cast<double>(y);
            return std::sqrt((x_ * x_) + (y_ * y_));
        }

        [[nodiscard]] constexpr Vec2<double> normalize() const {
            auto const mag = magnitude();
            return { static_cast<double>(x) / mag, static_cast<double>(y) / mag };
        }
    };

    using Vec2f = Vec2<float>;
    using Vec2d = Vec2<double>;
    using Vec2i = Vec2<int>;

    using Vec2u8  = Vec2<u8>;
    using Vec2u16 = Vec2<u16>;
    using Vec2u32 = Vec2<u32>;
    using Vec2u64 = Vec2<u64>;

    using Vec2i8  = Vec2<i8>;
    using Vec2i16 = Vec2<i16>;
    using Vec2i32 = Vec2<i32>;
    using Vec2i64 = Vec2<i64>;

    using Vec2usize = Vec2<usize>;
} // namespace cpt
