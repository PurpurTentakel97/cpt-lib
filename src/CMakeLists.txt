add_library(cpt_lib
            include/cpt/library.hpp
            library.cpp
)

target_include_directories(cpt_lib
                           PRIVATE include/cpt
                           INTERFACE include
)

target_link_libraries(cpt_lib
                      PRIVATE
                      project_options
                      spdlog::spdlog
)