//
// Purpur Tentakel
// cpp 23
// 05.05.24
//

#include "Strings.hpp"
#include <algorithm>
#include <gsl/narrow>

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

    std::vector<std::string_view> split(std::string_view const input, char const delimiter)
    {
        std::vector<std::string_view> output{};
        auto current = std::string_view::iterator{input.begin()};

        while (current != input.cend())
        {
            auto next = std::find_if(current, input.cend(),
                                     [delimiter](auto const c) { return c == delimiter; });
            output.emplace_back(input.substr(
                gsl::narrow<std::basic_string_view<char>::size_type>(std::distance(input.cbegin(), current)),
                gsl::narrow<std::basic_string_view<char>::size_type>(next - current)));
            current = next == input.cend() ? next : next + 1;
        }

        return output;
    }
}
