add_library(cpt-lib STATIC)

target_sources(cpt-lib
               PRIVATE
               Files.cpp
               Strings.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/cpt/Lib.hpp
               include/cpt/Concepts.hpp
               include/cpt/Files.hpp
               include/cpt/Strings.hpp
               include/cpt/Types.hpp
               include/cpt/Vec2.hpp
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
