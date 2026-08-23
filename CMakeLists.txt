cmake_minimum_required(VERSION 3.16)
project(jouw_project)

#find packages on pc?!
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

#get all the files and make them exectuable (c files)
file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(jouw_project WIN32 ${SOURCES})

#link the found libraries
target_link_libraries(jouw_project PRIVATE
    SDL2::SDL2
    SDL2::SDL2_ttf
    SDL2_image::SDL2_image
)