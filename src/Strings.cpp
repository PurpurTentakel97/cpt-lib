//
// Purpur Tentakel
// cpp 23
// 05.05.24
//

#include "Strings.hpp"
#include <algorithm>
#include <iomanip>
#include <ranges>

namespace cpt {
    std::string trim_copy(std::string_view input) {
        auto i = std::string{ input };
        trim(i);
        return i;
    }

    std::string ltrim_copy(std::string_view input) {
        auto i = std::string{ input };
        ltrim(i);
        return i;
    }

    std::string rtrim_copy(std::string_view input) {
        auto i = std::string{ input };
        rtrim(i);
        return i;
    }

    void trim(std::string& input) {
        rtrim(input);
        ltrim(input);
    }

    void ltrim(std::string& input) {
        input.erase(input.begin(), std::ranges::find_if(input, [](auto const c) {
                        return !std::isspace(static_cast<unsigned int>(c));
                    }));
    }

    void rtrim(std::string& input) {
        input.erase(std::find_if(input.rbegin(),
                                 input.rend(),
                                 [](auto const c) { return !std::isspace(static_cast<unsigned int>(c)); })
                            .base(),
                    input.end());
    }

    std::vector<std::string_view> split(std::string_view const input,
                                        std::string_view const delimiter,
                                        SplitBehavior const split_behavior) {
        std::vector<std::string_view> output{};
        auto ranges = (std::views::split(input, delimiter)
                       | std::views::transform([](auto const entry) { return static_cast<std::string_view>(entry); })
                       | std::views::filter([split_behavior](std::string_view const entry) {
                             return not entry.empty() or split_behavior == SplitBehavior::KeepEmptyParts;
                         }));
        // | std::ranges::to<std::vector<std::string_view>>();
        // todo: replace loop with std::ranges::to when GCC and Clang supports it.
        for (auto const r : ranges) {
            output.push_back(r);
        }

        return output;
    }
} // namespace cpt
