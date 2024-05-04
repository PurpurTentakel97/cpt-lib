cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_TOOLCHAIN_FILE  "${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(cpt_lib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${PROJECT_SOURCE_DIR}/dependencies.cmake)
find_packages()

include(${PROJECT_SOURCE_DIR}/project_options.cmake)

add_subdirectory(src bin)

if (${cpt_lib_tests})
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif ()
