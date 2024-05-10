cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(cpt_lib)

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

install(EXPORT cpt_lib-targets
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake
)

install(FILES cmake/cpt_lib-config.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake)
