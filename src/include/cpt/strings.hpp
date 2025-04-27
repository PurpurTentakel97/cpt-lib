//
// Purpur Tentakel
// 05.05.24
//

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace cpt {
    enum class SplitBehavior {
        SkipEmptyParts,
        KeepEmptyParts,
    };

    [[nodiscard]] std::string trim_copy(std::string_view input);
    [[nodiscard]] std::string ltrim_copy(std::string_view input);
    [[nodiscard]] std::string rtrim_copy(std::string_view input);

    void trim(std::string& input);
    void ltrim(std::string& input);
    void rtrim(std::string& input);

    [[nodiscard]] std::vector<std::string_view> split(std::string_view input,
                                                      std::string_view delimiter,
                                                      SplitBehavior split_behavior = SplitBehavior::KeepEmptyParts);
} // namespace cpt
