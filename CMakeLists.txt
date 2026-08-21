cmake_minimum_required(VERSION 3.16)
project(jouw_project)

# Zorg dat DLL's/so's in de build map komen
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Voeg SDL3 toe als subproject
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Maak een executable van al jouw .c bestanden in de 'src' map
file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(jouw_project WIN32 ${SOURCES})

# Link tegen SDL3
target_link_libraries(jouw_project PRIVATE SDL3::SDL3)