//
// Purpur Tentakel
// 08.05.24
//

#include <cpt/concepts.hpp>

using test_ty = int;

static_assert(cpt::IsOneOf<test_ty, int, float, double>);
static_assert(not cpt::IsOneOf<test_ty, float, double>);
