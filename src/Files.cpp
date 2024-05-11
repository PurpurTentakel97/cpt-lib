//
// Purpur Tentakel
// cpp 23
// 08.05.24
//

#include <cpt/Files.hpp>
#include <fstream>
#include <sstream>

namespace cpt {
    Result<std::string, ReadFileError> read_file(std::filesystem::path const& path) {
        auto const file = std::ifstream{ path };
        if (not file) {
            return Err{ ReadFileError::OpenFile };
        }
        auto stream = std::ostringstream{};
        stream << file.rdbuf();
        if (not stream) {
            return Err{ ReadFileError::ReadFromFile };
        }
        return std::move(stream).str();
    }
    Result<std::monostate, WriteFileError> write_file(std::filesystem::path const& path, std::string_view const contents) {
        auto file = std::ofstream{ path };
        if (not file) {
            return Err{ WriteFileError::OpenFile };
        }
        file << contents;
        if (not file) {
            return Err{ WriteFileError::WriteToFile };
        }
        return std::monostate();
    }
} // namespace cpt
