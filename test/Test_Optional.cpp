//
// Purpur Tentakel
// cpp 23
// 12.05.24
//


#include <cpt/Optional.hpp>
#include <gtest/gtest.h>

enum class Entry {
    default_entry,
    other_entry,
};

TEST(Optional, OK) {
    auto const optional = []() -> cpt::Optional<Entry> { return Entry::default_entry; }();

    ASSERT_TRUE(optional.ok());
    ASSERT_EQ(optional.unwrap(), Entry::default_entry);
    ASSERT_EQ(optional.unwrap_or_else([]() { return Entry::other_entry; }), Entry::default_entry);
    ASSERT_EQ(optional.unwrap_or_default(), Entry::default_entry);
}

TEST(Optional, Empty) {
    auto const optional = []() -> cpt::Optional<Entry> { return {}; }();

    auto const exception_check = [optional]() {
        try {
            [[maybe_unused]] auto const r = optional.unwrap();
        } catch (std::logic_error const& e) {
            ASSERT_STREQ(e.what(), "while unwrapping an optional");
            throw;
        }
    };

    ASSERT_FALSE(optional.ok());
    ASSERT_THROW(exception_check(), std::logic_error);
    ASSERT_EQ(optional.unwrap_or_else([]() { return Entry::other_entry; }), Entry::other_entry);
    ASSERT_EQ(optional.unwrap_or_default(), Entry::default_entry);
}
