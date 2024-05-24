add_executable(lib_test
               test_concepts.cpp
               test_files.cpp
               test_strings.cpp
               test_types.cpp
               test_vec2.cpp
)

target_link_libraries(lib_test
                      PRIVATE
                      cpt_lib_project_options
                      cpt-lib
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_test)
