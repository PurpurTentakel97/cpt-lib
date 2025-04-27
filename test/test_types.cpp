//
// Purpur Tentakel
// 07.05.24
//

#include <concepts>
#include <cpt/types.hpp>

static_assert(std::same_as<cpt::u8, std::uint8_t>);
static_assert(std::same_as<cpt::u16, std::uint16_t>);
static_assert(std::same_as<cpt::u32, std::uint32_t>);
static_assert(std::same_as<cpt::u64, std::uint64_t>);

static_assert(std::same_as<cpt::i8, std::int8_t>);
static_assert(std::same_as<cpt::i16, std::int16_t>);
static_assert(std::same_as<cpt::i32, std::int32_t>);
static_assert(std::same_as<cpt::i64, std::int64_t>);

static_assert(std::same_as<cpt::usize, std::size_t>);
