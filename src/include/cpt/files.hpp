//
// Purpur Tentakel
// 08.05.24
//

#pragma once
#include <filesystem>
#include <string>
#include <string_view>
#include <tl/expected.hpp>

namespace cpt {
    enum class ReadFileError {
        OpenFile,
        ReadFromFile,
    };

    enum class WriteFileError {
        OpenFile,
        WriteToFile,
    };

    [[nodiscard]] tl::expected<std::string, ReadFileError> read_file(std::filesystem::path const& path);

    [[nodiscard]] tl::expected<void, WriteFileError> write_file(std::filesystem::path const& path,
                                                                std::string_view contents);
} // namespace cpt
