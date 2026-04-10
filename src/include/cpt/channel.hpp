//
// Purpur Tentakel
// 10.04.26
//

#pragma once

#include <mutex>
#include <queue>
#include <tl/optional.hpp>

namespace cpt {
    template<typename T>
    class Sender;

    template<typename T>
    class Receiver;
} // namespace cpt

namespace cpt {
    template<typename T>
    class ChannelQueue final {
    public:
        friend class Sender<T>;
        friend class Receiver<T>;

    private:
        std::queue<T> m_buffer{};
        std::mutex m_mutex{};

        template<std::convertible_to<T> U>
        void push(U&& value) {
            auto const lock = std::lock_guard{ m_mutex };
            m_buffer.push(std::forward<U>(value));
        }

        [[nodiscard]] tl::optional<T> pop() {
            auto const lock = std::lock_guard{ m_mutex };

            if (m_buffer.empty()) {
                return {};
            }

            auto value = std::move(m_buffer.front());
            m_buffer.pop();
            return { std::move(value) };
        }
    };

    template<typename T>
    class Sender final {
        std::shared_ptr<ChannelQueue<T>> m_queue;

    public:
        template<std::convertible_to<T> U>
        void send(U&& value) {
            m_queue->push(std::forward<U>(value));
        }

        [[nodiscard]] Sender clone() const {
            return { m_queue };
        }
    };

    template<typename T>
    class Receiver final {
        std::shared_ptr<ChannelQueue<T>> m_queue;

    public:
        [[nodiscard]] tl::optional<T> receive() {
            return m_queue->pop();
        }

        [[nodiscard]] Receiver clone() const {
            return { m_queue };
        }
    };

    template<typename T>
    std::pair<Sender<T>, Receiver<T>> channel() {
        // The order here is important since the queue is moved into the receiver. It would be a use after move then.
        auto queue    = std::make_shared<ChannelQueue<T>>();
        auto sender   = Sender<T>{ queue };
        auto receiver = Receiver<T>{ std::move(queue) };
        return { std::move(sender), std::move(receiver) };
    }
} // namespace cpt
