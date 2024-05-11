add_library(cpt_lib STATIC)

target_sources(cpt_lib
               PRIVATE
               Files.cpp
               Strings.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/cpt/Concepts.hpp
               include/cpt/Files.hpp
               include/cpt/Lib.hpp
               include/cpt/Result.hpp
               include/cpt/Strings.hpp
               include/cpt/Types.hpp
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
