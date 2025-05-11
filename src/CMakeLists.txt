add_library(cpt__cpt_lib STATIC)

target_sources(cpt__cpt_lib
               PRIVATE
               files.cpp
               log.cpp
               strings.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/cpt/concepts.hpp
               include/cpt/files.hpp
               include/cpt/files.hpp
               include/cpt/lib.hpp
               include/cpt/log.hpp
               include/cpt/rect.hpp
               include/cpt/strings.hpp
               include/cpt/types.hpp
               include/cpt/unique_value.hpp
               include/cpt/vec2.hpp
)

target_include_directories(cpt__cpt_lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_system_libraries(cpt__cpt_lib
                             PUBLIC
                             tl::expected
                             tl::optional)
target_link_libraries(cpt__cpt_lib
                      PRIVATE $<BUILD_INTERFACE:cpt_lib_project_options>
)
