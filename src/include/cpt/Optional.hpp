//
// Purpur Tentakel
// cpp 23
// 12.05.24
//

#pragma once
#include <stdexcept>
#include <variant>
#include <concepts>

namespace cpt {
    template<typename T>
    class Optional final {
    private:
        std::variant<T, std::monostate> m_value;

    public:
        constexpr Optional(T&& value) : m_value{ std::in_place_index<0>, std::forward<T>(value) } { }
        constexpr Optional() : m_value{ std::in_place_index<1>, std::monostate() } { }

        [[nodiscard]] constexpr bool ok() const {
            return m_value.index() == 0;
        }

        [[nodiscard]] constexpr T& unwrap() {
            if (ok()) {
                return std::get<0>(m_value);
            }
            throw std::logic_error("while unwrapping an optional");
        }

        [[nodiscard]] constexpr T const& unwrap() const {
            if (ok()) {
                return std::get<0>(m_value);
            }
            throw std::logic_error("while unwrapping an optional");
        }

        template<typename  F> requires std::invocable<F>
        [[nodiscard]] constexpr T unwrap_or_else(F const& func) const {
            return ok() ? unwrap() : func();
        }

        [[nodiscard]] constexpr T unwrap_or_default() const requires(std::default_initializable<T>) {
            return ok() ? unwrap() : T();
        }
    };
} // namespace cpt
