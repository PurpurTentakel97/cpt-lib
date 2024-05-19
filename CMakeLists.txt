cmake_minimum_required(VERSION 3.23.0)

include(FetchContent)
FetchContent_Declare(vcpkg
                     GIT_REPOSITORY https://github.com/microsoft/vcpkg/
                     GIT_TAG 2024.03.25
)
FetchContent_MakeAvailable(vcpkg)

set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
project(cpt_lib)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${PROJECT_SOURCE_DIR}/project_options.cmake)

include(${PROJECT_SOURCE_DIR}/lib_dependencies.cmake)
find_lib_packages()

add_subdirectory(src bin)

if (${cpt_lib_tests})
    enable_testing()

    include(${PROJECT_SOURCE_DIR}/test_dependencies.cmake)
    find_test_packages()

    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif ()

install(TARGETS cpt-lib EXPORT cpt-lib-targets ARCHIVE
        FILE_SET HEADERS
)
install(EXPORT cpt-lib-targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
        NAMESPACE cpt::
)
install(FILES "cmake/cpt-lib-config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)
