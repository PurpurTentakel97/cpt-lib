//
// Purpur Tentakel
// cpp 23
// 07.05.24
//

#include <cpt/Types.hpp>
#include <cstddef>
#include <gtest/gtest.h>

TEST(TYPES, USIZE) {
    auto constexpr same = std::is_same_v<std::size_t, cpt::usize>;
    static_assert(same);
    ASSERT_TRUE(same);
}
