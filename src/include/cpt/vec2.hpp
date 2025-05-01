//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cmath>
#include <cpt/concepts.hpp>
#include <cpt/types.hpp>
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
                throw BadVec2Argument("division by 0");
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

    using Vec2_f = Vec2<float>;
    using Vec2_d = Vec2<double>;
    using Vec2_i = Vec2<int>;

    using Vec2_u8  = Vec2<u8>;
    using Vec2_u16 = Vec2<u16>;
    using Vec2_u32 = Vec2<u32>;
    using Vec2_u64 = Vec2<u64>;

    using Vec2_i8  = Vec2<i8>;
    using Vec2_i16 = Vec2<i16>;
    using Vec2_i32 = Vec2<i32>;
    using Vec2_i64 = Vec2<i64>;

    using Vec2_usize = Vec2<usize>;
} // namespace cpt
