add_executable(lib_test
               Test_Strings.cpp
               Test_Types.cpp
               Test_Files.cpp
               Test_Concepts.cpp
               Test_Vec2.cpp
)

target_link_libraries(lib_test
                      PRIVATE
                      cpt_lib_project_options
                      cpt_lib
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_test)
