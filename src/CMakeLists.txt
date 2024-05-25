add_library(cpt-lib STATIC)

target_sources(cpt-lib
               PRIVATE
               files.cpp
               strings.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/cpt/concepts.hpp
               include/cpt/files.hpp
               include/cpt/lib.hpp
               include/cpt/rect.hpp
               include/cpt/strings.hpp
               include/cpt/types.hpp
               include/cpt/vec2.hpp
)

target_include_directories(cpt-lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(cpt-lib
                      PUBLIC
                      tl::expected
                      PRIVATE
                      $<BUILD_INTERFACE:cpt_lib_project_options>
)
