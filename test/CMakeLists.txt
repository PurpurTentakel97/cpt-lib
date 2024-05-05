add_executable(my_test
               Test_Strings.cpp
)

target_link_libraries(my_test
                      PRIVATE
                      project_options
                      cpt_lib
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(my_test)
