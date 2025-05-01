//
// Purpur Tentakel
// 25.05.24
//

#pragma once

#include <tl/optional.hpp>
#include <utility>

namespace cpt {
    template<typename T>
    struct UniqueValueDeleter final {
        constexpr void operator()(T const&) { }
    };

    template<typename T, std::invocable<T> Deleter = UniqueValueDeleter<T>>
    class UniqueValue final {
    private:
        tl::optional<T> m_value;
        Deleter m_deleter;

    public:
        explicit constexpr UniqueValue(T value) : UniqueValue(std::move(value), Deleter{}) { }
        explicit constexpr UniqueValue(T value, Deleter deleter)
            : m_value{ std::move(value) },
              m_deleter{ std::move(deleter) } { }

        UniqueValue(UniqueValue const&)            = delete;
        UniqueValue& operator=(UniqueValue const&) = delete;

        UniqueValue(UniqueValue&& other) noexcept
            : m_value{ std::exchange(other.m_value, tl::nullopt) },
              m_deleter{ std::move(other.m_deleter) } { }

        UniqueValue& operator=(UniqueValue&& other) noexcept {
            if (this == std::addressof(other)) {
                return *this;
            }

            if (m_value.has_value()) {
                m_deleter(m_value.value());
            }
            m_deleter = Deleter{};

            m_value = std::exchange(other.m_value, tl::nullopt);
            std::swap(other.m_deleter, m_deleter);

            return *this;
        }

        constexpr ~UniqueValue() noexcept {
            if (m_value.has_value()) {
                m_deleter(m_value.value());
            }
        }

        [[nodiscard]] bool has_value() const {
            return m_value.has_value();
        }

        [[nodiscard]] T& value() {
            return m_value.value();
        }

        [[nodiscard]] T const& value() const {
            return m_value.value();
        }

        [[nodiscard]] explicit operator T&() {
            return value();
        }

        [[nodiscard]] explicit operator T const&() const {
            return value();
        }

        [[nodiscard]] T& operator*() {
            return value();
        }

        [[nodiscard]] T const& operator*() const {
            return value();
        }

        [[nodiscard]] T* operator->() {
            return &value();
        }

        [[nodiscard]] T const* operator->() const {
            return &value();
        }
    };
} // namespace cpt
