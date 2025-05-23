//
// Purpur Tentakel
// 08.05.24
//

#pragma once

#include <concepts>
#include <utility>
#include <limits>

namespace cpt {
    template<typename T, typename... Args>
    concept IsOneOf = (std::same_as<T, Args> or ...);

    template<typename T>
    concept IsNumeric = std::integral<T> or std::floating_point<T>;
}
