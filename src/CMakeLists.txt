add_library(cpt_lib
            include/cpt/Lib.hpp
            include/cpt/Files.hpp
            include/cpt/Strings.hpp
            include/cpt/Types.hpp
            include/cpt/Concepts.hpp
            Files.cpp
            Strings.cpp
)

target_include_directories(cpt_lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(cpt_lib
                      PUBLIC
                      tl::expected
                      PRIVATE
                      $<BUILD_INTERFACE:cpt_lib_project_options>
)

install(TARGETS cpt_lib
        EXPORT cpt_lib-targets
)
install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        FILES_MATCHING PATTERN "*.hpp"
)

