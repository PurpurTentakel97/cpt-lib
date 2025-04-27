//
// Purpur Tentakel
// 24.05.24
//

#pragma once

#include <cpt/concepts.hpp>
#include <cpt/types.hpp>

namespace cpt {
    template<IsNumeric T>
    struct Rect final {
        T x{};
        T y{};
        T width{};
        T height{};

        constexpr Rect() = default;
        constexpr Rect(T x_, T y_, T width_, T height) : x{ x_ }, y{ y_ }, width{ width_ }, height{ height } { }

        template<IsNumeric U>
        [[nodiscard]] constexpr Rect<U> to() const {
            return { static_cast<U>(x), static_cast<U>(y), static_cast<U>(width), static_cast<U>(height) };
        }

        [[nodiscard]] friend constexpr auto operator<=>(Rect const&, Rect const&) = default;
    };

    using Rect_f = Rect<float>;
    using Rect_d = Rect<double>;
    using Rect_i = Rect<int>;

    using Rect_u8  = Rect<u8>;
    using Rect_u16 = Rect<u16>;
    using Rect_u32 = Rect<u32>;
    using Rect_u64 = Rect<u64>;

    using Rect_i8  = Rect<i8>;
    using Rect_i16 = Rect<i16>;
    using Rect_i32 = Rect<i32>;
    using Rect_i64 = Rect<i64>;

    using Rect_usize = Rect<usize>;
} // namespace cpt
