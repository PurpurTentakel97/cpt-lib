//
// Purpur Tentakel
// cpp 23
// 12.05.24
//

#pragma once
#include <functional>
#include <stdexcept>
#include <variant>

namespace cpt {
    template<typename T>
    class Otional final {
    private:
        std::variant<T, std::monostate> m_value;

    public:
        Otional(T value) : m_value{ std::in_place_index<0>, std::forward<T>(value) } { }
        Otional() : m_value{ std::in_place_index<1>, std::forward<std::monostate>(std::monostate()) } { }

        [[nodiscard]] bool ok() const {
            return m_value.index() == 0;
        }

        [[nodiscard]] T unwrap() const {
            if (ok()) {
                return std::get<0>(m_value);
            }
            throw std::logic_error("while unwrapping an optional");
        }

        [[nodiscard]] T unwrap_or_else(std::function<T()> const& func) const {
            return ok() ? unwrap() : func();
        }

        [[nodiscard]] T unwrap_or_default() const requires(std::default_initializable<T>) {
            return ok() ? unwrap() : T();
        }
    };
} // namespace cpt
