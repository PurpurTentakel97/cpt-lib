add_executable(cpt__cpt_lib_test
               test_callback.cpp
               test_concepts.cpp
               test_files.cpp
               test_log.cpp
               test_strings.cpp
               test_types.cpp
               test_unique_value.cpp
               test_vec2.cpp
)

target_link_libraries(cpt__cpt_lib_test
                      PRIVATE
                      GTest::gtest_main
                      cpt_lib_project_options
                      cpt__cpt_lib
)

include(GoogleTest)
gtest_discover_tests(cpt__cpt_lib_test)
