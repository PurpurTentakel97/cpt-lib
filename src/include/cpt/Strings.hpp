//
// Purpur Tentakel
// cpp 23
// 05.05.24
//

#pragma once

#include <string>

namespace cpt
{
    [[nodiscard]] std::string trim_copy(std::string_view input);
    [[nodiscard]] std::string ltrim_copy(std::string_view input);
    [[nodiscard]] std::string rtrim_copy(std::string_view input);


    void trim(std::string& input);
    void ltrim(std::string& input);
    void rtrim(std::string& input);
}
