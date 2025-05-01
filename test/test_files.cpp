//
// Purpur Tentakel
// 08.05.24
//

#include <cpt/files.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include <tuple>


TEST(Files, ReadMissingDir) {
    auto const path      = std::filesystem::temp_directory_path() / "missing_dir" / "file.txt";
    auto constexpr error = cpt::ReadFileError::OpenFile;

    auto const result = cpt::read_file(path);
    ASSERT_FALSE(result.has_value()) << "error while reading file: should be open file error";
    ASSERT_EQ(result.error(), error);
}

TEST(Files, ReadMissingFile) {
    auto const path      = std::filesystem::temp_directory_path() / "missing_file.txt";
    auto constexpr error = cpt::ReadFileError::OpenFile;

    auto const result = cpt::read_file(path);
    ASSERT_FALSE(result.has_value()) << "error while reading file: should be read file error";
    ASSERT_EQ(result.error(), error);
}

TEST(Files, DoubleRead) {
    auto const path      = std::filesystem::temp_directory_path() / "new_file.txt";
    auto constexpr text  = "bester text evor";
    auto constexpr error = cpt::ReadFileError::ReadFromFile;

    auto file = std::ofstream{ path };
    ASSERT_TRUE(file) << "no valid file while open file (setup)";
    file << text;
    ASSERT_TRUE(file) << "no valid file while writing into file (setup)";

    auto const result = cpt::read_file(path);
    ASSERT_FALSE(result.has_value()) << "result contains value even tho it should not.";
    ASSERT_EQ(result.error(), error);

    file.close();
    ASSERT_TRUE(std::filesystem::remove(path)) << "error while deleting temp file";
}

TEST(Files, ReadFileSuccess) {
    auto const path     = std::filesystem::temp_directory_path() / "new_file.txt";
    auto constexpr text = "bester text evor";

    auto file = std::ofstream{ path };
    ASSERT_TRUE(file) << "no valid file while open file";
    file << text;
    ASSERT_TRUE(file) << "no valid file while writing into file";
    file.close();
    ASSERT_FALSE(file.is_open()) << "file still after writing into it";

    auto const result = cpt::read_file(path);
    ASSERT_TRUE(result.has_value()) << "error while reading file";
    ASSERT_EQ(result.value(), text) << "unexpected content in read file: expected: '" << text << "'; provided: '"
                                    << result.value() << "'";

    ASSERT_TRUE(std::filesystem::remove(path)) << "error while deleting temp file";
}

TEST(Files, WriteMissingDir) {
    auto const path        = std::filesystem::temp_directory_path() / "non_existing_dir" / "file_str.txt";
    auto constexpr content = "string";
    auto constexpr error   = cpt::WriteFileError::OpenFile;

    auto const result = cpt::write_file(path, content);
    ASSERT_FALSE(result.has_value()) << "missing error while writing file. This should fail.";
    ASSERT_EQ(result.error(), error);
}

TEST(Files, WriteSuccess) {
    auto const path = std::filesystem::temp_directory_path() / "new_file.txt";

    auto const result = cpt::write_file(path, "text");
    ASSERT_TRUE(result.has_value()) << "error while writing file";

    ASSERT_TRUE(std::filesystem::remove(path)) << "error while deleting temp file";
}

TEST(Files, ReadWriteSuccsess) {
    auto const path     = std::filesystem::temp_directory_path() / "new_file.txt";
    auto constexpr text = "best text evor\nreally";

    auto const result_write = cpt::write_file(path, text);
    ASSERT_TRUE(result_write.has_value()) << "error while writing file";

    auto const result_read = cpt::read_file(path);
    ASSERT_TRUE(result_read.has_value()) << "error while reading file";
    ASSERT_EQ(result_read.value(), text) << "unexpected content after reading file: loaded: '" << result_read.value()
                                         << "'; saved: '" << text << "'";

    ASSERT_TRUE(std::filesystem::remove(path)) << "error while deleting temp file";
}
