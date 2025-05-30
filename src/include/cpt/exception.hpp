//
// Purpur Tentakel
// 30.05.25
//

#pragma once

#include <stdexcept>

namespace cpt {
    /**
     * use for any kind of error inside the uil::Callback class.
     */
    class CallbackException final : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
} // namespace cpt
