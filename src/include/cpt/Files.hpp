//
// Purpur Tentakel
// cpp 23
// 08.05.24
//

#pragma once
#include <cpt/Result.hpp>
#include <filesystem>
#include <string>
#include <string_view>

namespace cpt {
    enum class ReadFileError {
        OpenFile,
        ReadFromFile,
    };

    enum class WriteFileError {
        OpenFile,
        WriteToFile,
    };

    [[nodiscard]] Result<std::string, ReadFileError> read_file(std::filesystem::path const& path);

    [[nodiscard]] Result<std::monostate, WriteFileError> write_file(std::filesystem::path const& path, std::string_view contents);
} // namespace cpt
