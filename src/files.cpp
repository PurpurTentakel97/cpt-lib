//
// Purpur Tentakel
// cpp 23
// 08.05.24
//

#include <cpt/files.hpp>
#include <fstream>
#include <sstream>

namespace cpt {
    tl::expected<std::string, ReadFileError> read_file(std::filesystem::path const& path) {
        auto const file = std::ifstream{ path };
        if (not file) {
            return tl::unexpected{ ReadFileError::OpenFile };
        }
        auto stream = std::ostringstream{};
        stream << file.rdbuf();
        if (not stream) {
            return tl::unexpected{ ReadFileError::ReadFromFile };
        }
        return std::move(stream).str();
    }
    tl::expected<void, WriteFileError> write_file(std::filesystem::path const& path, std::string_view const contents) {
        auto file = std::ofstream{ path };
        if (not file) {
            return tl::unexpected{ WriteFileError::OpenFile };
        }
        file << contents;
        if (not file) {
            return tl::unexpected{ WriteFileError::WriteToFile };
        }
        return {};
    }
} // namespace cpt
