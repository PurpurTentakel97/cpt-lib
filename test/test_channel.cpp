//
// Purpur Tentakel
// 10.04.26
//

#include <cpt/channel.hpp>
#include <gtest/gtest.h>
#include <string>
#include <thread>

TEST(Channel, NotDefaultConstructible) {
    static_assert(not std::default_initializable<cpt::Sender<int>>);
    static_assert(not std::default_initializable<cpt::Receiver<int>>);
    static_assert(not std::default_initializable<cpt::Channel<int>>);
}

TEST(Channel, Create) {
    [[maybe_unused]] auto [sender, receiver]   = cpt::channel<int>();
    [[maybe_unused]] auto [sender2, receiver2] = cpt::Channel<int>::create();
}

TEST(Channel, SendAndReceive) {
    auto [sender, receiver] = cpt::channel<int>();

    sender.send(42);
    auto const result = receiver.receive();

    ASSERT_TRUE(result.has_value()) << "expected a value but received nothing.";
    EXPECT_EQ(result.value(), 42) << "unexpected value.\nexpected: 42\nprovided: " << result.value();
}

TEST(Channel, ReceiveEmptyReturnsNullopt) {
    auto [sender, receiver] = cpt::channel<int>();

    auto const result = receiver.receive();
    EXPECT_FALSE(result.has_value()) << "expected no value on empty channel but got one.";
}

TEST(Channel, SendMultipleReceiveInOrder) {
    auto [sender, receiver] = cpt::channel<int>();

    sender.send(1);
    sender.send(2);
    sender.send(3);

    auto const r1 = receiver.receive();
    auto const r2 = receiver.receive();
    auto const r3 = receiver.receive();

    ASSERT_TRUE(r1.has_value()) << "expected value 1 but received nothing.";
    ASSERT_TRUE(r2.has_value()) << "expected value 2 but received nothing.";
    ASSERT_TRUE(r3.has_value()) << "expected value 3 but received nothing.";

    EXPECT_EQ(r1.value(), 1) << "unexpected first value.\nexpected: 1\nprovided: " << r1.value();
    EXPECT_EQ(r2.value(), 2) << "unexpected second value.\nexpected: 2\nprovided: " << r2.value();
    EXPECT_EQ(r3.value(), 3) << "unexpected third value.\nexpected: 3\nprovided: " << r3.value();
}

TEST(Channel, ReceiveExhaustChannel) {
    auto [sender, receiver] = cpt::channel<int>();

    sender.send(10);

    auto const r1 = receiver.receive();
    auto const r2 = receiver.receive();

    ASSERT_TRUE(r1.has_value()) << "expected a value but received nothing on first receive.";
    EXPECT_FALSE(r2.has_value()) << "expected no value on second receive but got one.";
}

TEST(Channel, SendMoveOnlyType) {
    auto [sender, receiver] = cpt::channel<std::unique_ptr<int>>();

    sender.send(std::make_unique<int>(99));
    auto const result = receiver.receive();

    ASSERT_TRUE(result.has_value()) << "expected a value but received nothing.";
    ASSERT_NE(result.value(), nullptr) << "received a null pointer.";
    EXPECT_EQ(*result.value(), 99) << "unexpected value.\nexpected: 99\nprovided: " << *result.value();
}

TEST(Channel, SendStringType) {
    auto [sender, receiver] = cpt::channel<std::string>();

    sender.send(std::string{ "hello" });
    auto const result = receiver.receive();

    ASSERT_TRUE(result.has_value()) << "expected a value but received nothing.";
    EXPECT_EQ(result.value(), "hello") << "unexpected value.\nexpected: hello\nprovided: " << result.value();
}

TEST(Channel, ClonedSenderSharesQueue) {
    auto [sender, receiver] = cpt::channel<int>();

    auto const sender2 = sender.clone();

    sender.send(1);
    sender2.send(2);

    auto const r1 = receiver.receive();
    auto const r2 = receiver.receive();

    ASSERT_TRUE(r1.has_value()) << "expected first value but received nothing.";
    ASSERT_TRUE(r2.has_value()) << "expected second value but received nothing.";

    EXPECT_EQ(r1.value(), 1) << "unexpected first value.\nexpected: 1\nprovided: " << r1.value();
    EXPECT_EQ(r2.value(), 2) << "unexpected second value.\nexpected: 2\nprovided: " << r2.value();
}

TEST(Channel, ClonedReceiverSharesQueue) {
    auto [sender, receiver] = cpt::channel<int>();

    auto const receiver2 = receiver.clone();

    sender.send(10);
    sender.send(20);

    auto const r1 = receiver.receive();
    auto const r2 = receiver2.receive();

    ASSERT_TRUE(r1.has_value()) << "expected first value but received nothing.";
    ASSERT_TRUE(r2.has_value()) << "expected second value but received nothing.";

    EXPECT_EQ(r1.value(), 10) << "unexpected first value.\nexpected: 10\nprovided: " << r1.value();
    EXPECT_EQ(r2.value(), 20) << "unexpected second value.\nexpected: 20\nprovided: " << r2.value();
}

TEST(Channel, MultithreadedSendReceive) {
    auto [sender, receiver] = cpt::channel<int>();

    constexpr int message_count = 100;

    std::thread producer{ [&sender]() {
        for (int i = 0; i < message_count; ++i) {
            sender.send(i);
        }
    } };

    producer.join();

    int received_count = 0;
    while (receiver.receive().has_value()) {
        ++received_count;
    }

    EXPECT_EQ(received_count, message_count) << "unexpected number of received messages.\nexpected: " << message_count
                                             << "\nprovided: " << received_count;
}

TEST(Channel, MultithreadedMultipleSenders) {
    auto [sender, receiver] = cpt::channel<int>();

    constexpr int messages_per_thread = 50;
    constexpr int thread_count        = 4;

    auto const worker = [](cpt::Sender<int> s) {
        for (int i = 0; i < messages_per_thread; ++i) {
            s.send(i);
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(thread_count);
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(worker, sender.clone());
    }

    for (auto& t : threads) {
        t.join();
    }

    int received_count = 0;
    while (receiver.receive().has_value()) {
        ++received_count;
    }

    EXPECT_EQ(received_count, messages_per_thread * thread_count)
            << "unexpected number of received messages.\nexpected: " << messages_per_thread * thread_count
            << "\nprovided: " << received_count;
}

TEST(Channel, Termination) {
    auto [sender, receiver] = cpt::channel<int>();

    EXPECT_FALSE(sender.is_terminating());
    EXPECT_FALSE(receiver.should_terminate());

    sender.terminate();

    EXPECT_TRUE(sender.is_terminating());
    EXPECT_TRUE(receiver.should_terminate());
}

TEST(Channel, SendSafe) {
    auto [sender, receiver] = cpt::channel<int>();

    sender.send_safe(1);
    EXPECT_TRUE(receiver.receive().has_value());

    sender.terminate();
    sender.send_safe(2);
    EXPECT_FALSE(receiver.receive().has_value());
}

TEST(Channel, HasPendingMessages) {
    auto [sender, receiver] = cpt::channel<int>();

    EXPECT_FALSE(receiver.has_pending_messages());

    sender.send(1);
    EXPECT_TRUE(receiver.has_pending_messages());

    [[maybe_unused]] auto const _ = receiver.receive();
    EXPECT_FALSE(receiver.has_pending_messages());
}

TEST(Channel, ShouldTerminateSafe) {
    auto [sender, receiver] = cpt::channel<int>();

    EXPECT_FALSE(receiver.should_terminate_safe());

    sender.terminate();
    EXPECT_TRUE(receiver.should_terminate_safe());

    auto [sender2, receiver2] = cpt::channel<int>();
    sender2.send(1);
    sender2.terminate();
    EXPECT_FALSE(receiver2.should_terminate_safe()); // has pending messages

    [[maybe_unused]] auto const __ = receiver2.receive();
    EXPECT_TRUE(receiver2.should_terminate_safe()); // no more pending messages
}

TEST(Channel, ConstSender) {
    auto const [sender, receiver] = cpt::channel<int>();
    sender.send(1);
    sender.send_safe(2);
    [[maybe_unused]] auto const value = sender.clone();
    sender.terminate();
    [[maybe_unused]] auto const value2 = sender.is_terminating();
}

TEST(Channel, ConstReceiver) {
    auto const [sender, receiver] = cpt::channel<int>();
    [[maybe_unused]] auto const value = receiver.receive();
    [[maybe_unused]] auto const value2 = receiver.clone();
    [[maybe_unused]] auto const value3 = receiver.should_terminate_safe();
    [[maybe_unused]] auto const value4 = receiver.should_terminate();
    [[maybe_unused]] auto const value5 = receiver.has_pending_messages();
}
