cmake_minimum_required(VERSION 3.0)

project(dep)

# SDL2
add_subdirectory(${PROJECT_SOURCE_DIR}/SDL2)
set( SDL_STATIC OFF CACHE BOOL "Build the static SDL library" )
set( SDL_SHARED ON CACHE BOOL "Build the shared SDL library" )
add_definitions( -DSDL_MAIN_HANDLED )   # Important : no sdl-main compile
set( EXTRA_LIBS ${EXTRA_LIBS} SDL2 )
# set_target_properties(SDL2 PROPERTIES OUTPUT_NAME "SDL2")

# glad
add_subdirectory(${PROJECT_SOURCE_DIR}/glad)

# change output dir
set_target_properties( SDL2 glad
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../lib"
    
)

