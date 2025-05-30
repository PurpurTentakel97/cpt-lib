//
// Purpur Tentakel
// 17.05.24
//

#include <gtest/gtest.h>
#include <cpt/callback.hpp>

TEST(Callbacks, CallsCallbackOnce) {
    auto callbacks = cpt::Callback();
    auto counter   = 0;
    callbacks += [&counter]() { ++counter; };

    EXPECT_EQ(counter, 0);
    callbacks.invoke();
    EXPECT_EQ(counter, 1);
    EXPECT_EQ(callbacks.size(), 1);
}

TEST(Callbacks, CallsCallbackClear) {
    auto callbacks = cpt::Callback();
    auto counter   = 0;
    callbacks += [&counter]() { ++counter; };

    callbacks.clear();
    callbacks.invoke();
    EXPECT_EQ(counter, 0);
    EXPECT_TRUE(callbacks.is_empty());
}

TEST(Callbacks, MultipleCallbacks) {
    auto callbacks = cpt::Callback();
    auto counter_1   = 0;
    auto counter_2   = 0;
    callbacks += [&counter_1]() { ++counter_1; };
    callbacks += [&counter_2]() { ++counter_2; };

    EXPECT_EQ(counter_1, 0);
    EXPECT_EQ(counter_2, 0);
    callbacks.invoke();
    EXPECT_EQ(counter_1, 1);
    EXPECT_EQ(counter_2, 1);
    EXPECT_EQ(callbacks.size(), 2);
}

TEST(Callbacks, AddInvalidFunction) {
    auto callbacks = cpt::Callback();
    std::function<void()> func;

    try {
        callbacks += func;
        GTEST_FAIL() << "cpt::CallbackException not thrown";
    }
    catch(cpt::CallbackException const& e) {
        EXPECT_STREQ(e.what(), "register of a bad callback function");
    }
}
