cmake_minimum_required(VERSION 3.0)

project(dep)

# SDL2
set( SDL_STATIC OFF CACHE BOOL "Build the static SDL library" )
set( SDL_SHARED ON CACHE BOOL "Build the shared SDL library" )
add_definitions( -DSDL_MAIN_HANDLED )   # Important : no sdl-main compile
set( EXTRA_LIBS ${EXTRA_LIBS} SDL2 )
add_subdirectory(${PROJECT_SOURCE_DIR}/SDL2)
# set_target_properties(SDL2 PROPERTIES OUTPUT_NAME "SDL2")

# glad
add_subdirectory(${PROJECT_SOURCE_DIR}/glad)

# glm
set( BUILD_STATIC_LIBS OFF CACHE BOOL "Build the static glm library" )
set( BUILD_SHARED_LIBS ON CACHE BOOL "Build the shared glm library" )
set( GLM_TEST_ENABLE OFF CACHE BOOL "Build unit tests" )
add_subdirectory(${PROJECT_SOURCE_DIR}/glm)

# freetype
add_definitions(-DFT_CONFIG_OPTION_PIC)
add_subdirectory(${PROJECT_SOURCE_DIR}/freetype)

# freetype-gl
include_directories(${PROJECT_SOURCE_DIR}/glad/include ${PROJECT_SOURCE_DIR}/freetype/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/freetype-gl)

# spdlog
add_subdirectory(${PROJECT_SOURCE_DIR}/spdlog)

# imgui
add_subdirectory(${PROJECT_SOURCE_DIR}/imgui)

# imgui docking
add_subdirectory(${PROJECT_SOURCE_DIR}/imgui-docking)

# change output dir
set_target_properties( SDL2 glad glm_shared freetype freetype-gl spdlog imgui imgui-docking
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../lib"
)