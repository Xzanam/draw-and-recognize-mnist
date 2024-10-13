cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(MNISTCHARACTERRECOG)

find_package(Torch REQUIRED)

# Manually specify the include directories and library for Ncurses
include_directories(/usr/include)
link_libraries(ncurses)

add_executable(character_recog characterrecog.cc)
target_link_libraries(character_recog "${TORCH_LIBRARIES}" ncurses)
set_property(TARGET character_recog PROPERTY CXX_STANDARD 17)
