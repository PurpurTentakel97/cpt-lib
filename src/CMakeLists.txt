add_library(cpt_lib
            include/cpt/Lib.hpp
            include/cpt/Files.hpp
            include/cpt/Strings.hpp
            include/cpt/Types.hpp
            Files.cpp
            Strings.cpp
)

target_include_directories(cpt_lib
                           PRIVATE include/cpt
                           INTERFACE include
)

target_link_libraries(cpt_lib
                      PRIVATE
                      project_options
)
