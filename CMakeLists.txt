cmake_minimum_required(VERSION 3.16)
project(jouw_project)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)   # ← Zoek SDL2_image
find_package(SDL2_ttf REQUIRED)     # ← Zoek SDL2_ttf

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(jouw_project WIN32 ${SOURCES})

target_link_libraries(jouw_project PRIVATE 
    SDL2::SDL2 
    SDL2_image::SDL2_image   # ← Let op: SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf       # ← Let op: SDL2_ttf::SDL2_ttf
)
# Optioneel: voor SDL_main op Windows
#target_compile_definitions(jouw_project PRIVATE SDL_MAIN_HANDLED)