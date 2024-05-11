//
// Purpur Tentakel
// cpp 23
// 11.05.24
//

#pragma once
#include <functional>
#include <stdexcept>
#include <variant>

namespace cpt {
    template<typename E>
    struct Err final {
    private:
        E m_value;

    public:
        explicit Err(E value) : m_value{ std::move(value) } { }

        [[nodiscard]] E value() const {
            return m_value;
        }
    };

    template<typename T, typename E>
    class Result final {
    private:
        std::variant<T, E> m_value;

    public:
        Result(T value) : m_value{ std::in_place_index<0>, std::forward<T>(value) } { }
        Result(Err<E> value) : m_value{ std::in_place_index<1>, std::forward<E>(value.value()) } { }

        [[nodiscard]] bool ok() const {
            return m_value.index() == 0;
        }

        [[nodiscard]] bool err() const {
            return not ok();
        }

        [[nodiscard]] T unwrap() const {
            if (ok()) {
                return std::get<0>(m_value);
            }
            throw std::logic_error("while unwrapping a result with 'unwarp'");
        }

        [[nodiscard]] E unwrap_err() const {
            if (err()) {
                return std::get<1>(m_value);
            }
            throw std::logic_error("while unwrapping an result with 'unwrap_err'");
        }

        [[nodiscard]] T unwrap_or(T const& other) const {
            return ok() ? unwrap() : other;
        }

        [[nodiscard]] T unwarp_or_else(std::function<T()> const& func) const {
            return ok() ? unwrap() : func();
        }

        [[nodiscard]] T unwrap_or_default() const {
            return ok() ? unwrap() : T();
        }
    };
} // namespace cpt
