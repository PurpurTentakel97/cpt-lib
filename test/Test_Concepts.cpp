//
// Purpur Tentakel
// cpp 23
// 08.05.24
//

#include <cpt/Concepts.hpp>

using test_ty = int;

static_assert(cpt::IsOneOf<test_ty, int, float, double>);
static_assert(not cpt::IsOneOf<test_ty, float, double>);
