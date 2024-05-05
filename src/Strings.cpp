//
// Purpur Tentakel
// cpp 23
// 05.05.24
//

#include "Strings.hpp"
#include <algorithm>

namespace cpt
{
    std::string trim_copy(std::string_view input)
    {
        auto i = std::string{input};
        trim(i);
        return i;
    }

    std::string ltrim_copy(std::string_view input)
    {
        auto i = std::string{input};
        ltrim(i);
        return i;
    }

    std::string rtrim_copy(std::string_view input)
    {
        auto i = std::string{input};
        rtrim(i);
        return i;
    }

    void trim(std::string& input)
    {
        rtrim(input);
        ltrim(input);
    }

    void ltrim(std::string& input)
    {
        input.erase(input.begin(), std::ranges::find_if(input,
                                                        [](auto const c) { return !std::isspace(c); }));
    }

    void rtrim(std::string& input)
    {
        input.erase(std::find_if(input.rbegin(), input.rend(),
                                 [](auto const& c) { return !std::isspace(c); }).base(),
                    input.end());
    }
}
