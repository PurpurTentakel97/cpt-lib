cmake_minimum_required(VERSION 3.22.1)
project(cpt_lib)

set(CMAKE_CXX_STANDARD 23)

include(dependencies.cmake)
find_packages()

include(project_options.cmake)

add_subdirectory(src)
