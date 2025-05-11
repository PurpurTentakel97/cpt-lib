find_package(tl-expected CONFIG REQUIRED)
find_package(tl-optional CONFIG REQUIRED)

if (cpt_lib_enable_tests)
    find_package(GTest CONFIG REQUIRED)
endif ()
