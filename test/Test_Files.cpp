//
// Purpur Tentakel
// cpp 23
// 08.05.24
//

#include <cpt/Files.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include <tuple>


TEST(Files, ReadMissingDir) {
    auto const path      = std::filesystem::path("missing_dir") / "file.txt";
    auto constexpr error = cpt::ReadFileError::OpenFile;

    auto const result = cpt::read_file(path);
    ASSERT_FALSE(result.has_value());
    ASSERT_EQ(result.error(), error);
}

TEST(Files, ReadMissingFile) {
    auto const path      = std::filesystem::path("missing_file.txt");
    auto constexpr error = cpt::ReadFileError::OpenFile;

    auto const result = cpt::read_file(path);
    ASSERT_FALSE(result.has_value());
    ASSERT_EQ(result.error(), error);
}

TEST(Files, DoubleRead) {
    auto const path      = std::filesystem::path("missing_file.txt");
    auto constexpr text  = "bester text evor";
    auto constexpr error = cpt::ReadFileError::ReadFromFile;

    auto file = std::ofstream{ path };
    ASSERT_TRUE(file);
    file << text;
    ASSERT_TRUE(file);

    auto const result = cpt::read_file(path);
    ASSERT_FALSE(result.has_value());
    ASSERT_EQ(result.error(), error);

    file.close();
    ASSERT_TRUE(std::filesystem::remove(path));
}

TEST(Files, ReadFileSuccess) {
    auto const path     = std::filesystem::path("new_file.txt");
    auto constexpr text = "bester text evor";

    auto file = std::ofstream{ path };
    ASSERT_TRUE(file);
    file << text;
    ASSERT_TRUE(file);
    file.close();
    ASSERT_FALSE(file.is_open());

    auto const result = cpt::read_file(path);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), text);

    ASSERT_TRUE(std::filesystem::remove(path));
}

TEST(Files, WriteMissingDir) {
    auto const path        = std::filesystem::path("non_exsisting_dir") / "file_str.txt";
    auto constexpr contens = "string";
    auto constexpr error   = cpt::WriteFileError::OpenFile;

    auto const result = cpt::write_file(path, contens);
    ASSERT_FALSE(result.has_value());
    ASSERT_EQ(result.error(), error);
}

TEST(Files, WriteSuccess) {
    auto const path = std::filesystem::path("new_file.txt");

    auto const result = cpt::write_file(path, "text");
    ASSERT_TRUE(result.has_value());

    ASSERT_TRUE(std::filesystem::remove(path));
}

TEST(Files, ReadWriteSuccsess) {
    auto const path     = std::filesystem::path("new_file.txt");
    auto constexpr text = "best text evor\nreally";

    auto const result_write = cpt::write_file(path, text);
    ASSERT_TRUE(result_write.has_value());

    auto const result_read = cpt::read_file(path);
    ASSERT_TRUE(result_read.has_value());
    ASSERT_EQ(result_read.value(), text);

    ASSERT_TRUE(std::filesystem::remove(path));
}
