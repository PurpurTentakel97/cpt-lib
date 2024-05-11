//
// Purpur Tentakel
// cpp 23
// 11.05.24
//

#pragma once
#include <stdexcept>
#include <variant>

namespace cpt {
    template<typename T, typename E>
    class Result final {
    private:
        std::variant<T, E> m_value;

    public:
        explicit Result(T value) : m_value{ std::move(value) } { }
        explicit Result(E value) : m_value{ std::move(value) } { }

        [[nodiscard]] bool ok() const {
            return std::holds_alternative<T>(m_value);
        }

        [[nodiscard]] bool err() const {
            return not ok();
        }

        [[nodiscard]] T unwrap() const {
            if (ok()) {
                return std::get<T>(m_value);
            }
            throw std::logic_error("while unwrapping a result with 'unwarp'");
        }

        [[nodiscard]] E unwrap_err() const {
            if (err()) {
                return std::get<E>(m_value);
            }
            throw std::logic_error("while unwrapping an result with 'unwrap_err'");
        }

        [[nodiscard]] T unwrap_or(T const& other) const {
            return ok() ? unwrap() : other;
        }
    };
} // namespace cpt
