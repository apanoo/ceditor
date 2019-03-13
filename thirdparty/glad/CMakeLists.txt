project(glad)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(glad SHARED
    src/glad.c
)

# Output
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)