cmake_minimum_required(VERSION 3.30.3)

project(cpt__cpt_lib)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${PROJECT_SOURCE_DIR}/cmake/project_options.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/SystemLink.cmake)
add_subdirectory(external)
add_subdirectory(src bin)

if (${cpt_lib_enable_tests})
    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif ()

install(TARGETS cpt__cpt_lib EXPORT cpt__cpt_lib_targets ARCHIVE
        FILE_SET HEADERS
)
install(EXPORT cpt__cpt_lib_targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
        NAMESPACE cpt::
)
install(FILES "cmake/cpt-lib-config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)
