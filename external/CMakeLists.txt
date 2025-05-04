include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)

CPMAddPackage(
        NAME TL_EXPECTED
        GITHUB_REPOSITORY TartanLlama/expected
        VERSION 1.1.0
        OPTIONS
        "EXPECTED_BUILD_PACKAGE OFF"
        "EXPECTED_BUILD_TESTS OFF"
        "EXPECTED_BUILD_PACKAGE_DEB OFF"
)
CPMAddPackage(
        NAME TL_OPTIONAL
        GITHUB_REPOSITORY TartanLlama/optional
        VERSION 1.1.0
        OPTIONS
        "OPTIONAL_BUILD_PACKAGE OFF"
        "OPTIONAL_BUILD_TESTS OFF"
        "OPTIONAL_BUILD_PACKAGE_DEB OFF"
)
if (cpt_lib_enable_tests)
    CPMAddPackage(
            NAME GOOGLE_TEST
            GITHUB_REPOSITORY google/googletest
            VERSION 1.14.0
            OPTIONS
            "BUILD_GMOCK OFF"
            "INSTALL_GTEST OFF"
    )
endif ()
