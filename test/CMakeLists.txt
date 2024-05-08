add_executable(lib_test
               Test_Strings.cpp
               Test_Types.cpp
               Test_Files.cpp
)

target_link_libraries(lib_test
                      PRIVATE
                      project_options
                      cpt_lib
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_test)
