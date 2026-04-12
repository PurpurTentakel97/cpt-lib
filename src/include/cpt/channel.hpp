//
// Purpur Tentakel
// 10.04.26
//

#pragma once

#include <memory>
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
    class Channel final {
    private:
        class ChannelKeyPass { };

    public:
        friend class Sender<T>;
        friend class Receiver<T>;

        explicit Channel(ChannelKeyPass const&) { };

        [[nodiscard]] static std::pair<Sender<T>, Receiver<T>> create() {
            // The order here is important since the queue is moved into the receiver. It would be a use after move then.
            auto queue    = std::make_shared<Channel>(ChannelKeyPass{});
            auto sender   = Sender<T>{ queue };
            auto receiver = Receiver<T>{ std::move(queue) };
            return { std::move(sender), std::move(receiver) };
        }

    private:
        std::queue<T> m_buffer{};
        std::mutex m_mutex{};

        void push(T value) {
            auto const lock = std::lock_guard{ m_mutex };
            m_buffer.push(std::move(value));
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
    }; // namespace detail

    template<typename T>
    class Sender final {
        std::shared_ptr<Channel<T>> m_queue;

    public:
        explicit Sender(std::shared_ptr<Channel<T>> queue) : m_queue{ std::move(queue) } { }

        void send(T value) const {
            m_queue->push(std::move(value));
        }

        [[nodiscard]] Sender clone() const {
            return Sender{ m_queue };
        }
    };

    template<typename T>
    class Receiver final {
        std::shared_ptr<Channel<T>> m_queue;

    public:
        explicit Receiver(std::shared_ptr<Channel<T>> queue) : m_queue{ std::move(queue) } { }

        [[nodiscard]] tl::optional<T> receive() const {
            return m_queue->pop();
        }

        [[nodiscard]] Receiver clone() const {
            return Receiver{ m_queue };
        }
    };

    template<typename T>
    std::pair<Sender<T>, Receiver<T>> channel() {
        return Channel<T>::create();
    }
} // namespace cpt
