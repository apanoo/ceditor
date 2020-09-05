#####
### Only for android now TODO: use cmake on Linux/Win/Mac
#####

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(ceditor C CXX)

# Check and suport c++ 11
include( CheckCXXCompilerFlag )  
CHECK_CXX_COMPILER_FLAG( "-std=c++11" COMPILER_SUPPORTS_CXX11 )  
CHECK_CXX_COMPILER_FLAG( "-std=c++0x" COMPILER_SUPPORTS_CXX0X )  
if( COMPILER_SUPPORTS_CXX11 )  
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )  
elseif( COMPILER_SUPPORTS_CXX0X )  
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )  
else()  
     message( FATAL "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler." )  
endif() 


#
# Set some helper variables.
#
string(TOLOWER "${CMAKE_SYSTEM_NAME}" targetSystem)
set(projectDir  "${CMAKE_CURRENT_LIST_DIR}")
set(sourceDir   "${projectDir}/core")
set(targetName  "SimpleExample")
set(binDir      "${projectDir}/bin")

# Define executable output dir.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${binDir}/${targetSystem}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${binDir}/${targetSystem}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${binDir}/${targetSystem}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${binDir}/${targetSystem}_debug")


#
# Dependencies:
#   Using SDL as a subproject for simplicity.
#   NOTE: This means that CMAKE_C_FLAGS set anywhere here are also passed to SDL.
#
if(MINGW)
  set(VIDEO_OPENGLES OFF CACHE STRING "")
endif()

set(sdlDir "${projectDir}/thirdparty/SDL2")
set(glmDir "${projectDir}/thirdparty/glm")
set(freetypeDir "${projectDir}/thirdparty/freetype")
set(gladDir "${projectDir}/thirdparty/glad")
set(spdlogDir "${projectDir}/thirdparty/spdlog")
set(imguiDir "${projectDir}/thirdparty/imgui")
set(trayDir "${projectDir}/thirdparty/tray")
set(imguiDocking "${projectDir}/thirdparty/imgui-docking")
add_subdirectory(${sdlDir} EXCLUDE_FROM_ALL)
add_subdirectory(${gladDir})
add_subdirectory(${spdlogDir})
add_subdirectory(${imguiDir})
add_subdirectory(${imguiDocking})
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2)
set(GLAD_LIBRARY glad)
set(SPDLOG_LIBRARY spdlog)
set(IMGUI_LIBRARY imgui)
set(IMGUI_DOCKING imgui-docking)


# Joysticks were causing trouble on android.
add_definitions(-DSDL_JOYSTICK=0)

#
# Sources (relative to the project root dir).
#
set(projectSources
  editor/main-docking.cpp
  editor/imgui_demo.cpp
  editor/plot/implot.cpp
  editor/plot/implot_items.cpp

  # log
  core/logger/log.cpp
  # imgui
  core/2d/gui/imgui_impl_opengl3.cpp
  core/2d/gui/imgui_impl_sdl.cpp

  # Use this instead for an opengl example
  #source/main_opengl.c
)

# Include dirs.
set(projectIncludeDirs ${projectIncludeDirs}
  "${sdlDir}/include"
  "${glmDir}"
  "${projectDir}"
  "${sourceDir}"
  "${freetypeDir}/include"
  "${gladDir}/include"
  "${spdlogDir}/include"
  # "${imguiDir}"
  "${imguiDocking}"
  # "${trayDir}"
)

message("     Sources: ${projectSources}\n")
message("Include dirs: ${projectIncludeDirs}\n")


#
# Platform dependent stuff.
#

if(NOT ANDROID)
  find_package(OpenGL REQUIRED)
endif()

if(EMSCRIPTEN)
  # This makes emscripten build a html page in addition to the js code.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")

  # Embedding and mapping files at from_path@to_path
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ../../assets@/")

  # Emscripten requires static linking.
  set(SDL2_LIBRARY SDL2-static)
endif()

#
# Build the binary.
# -----------------------------------------------------------------------
#
if(ANDROID)
  # On android the final binary is a shared library not an executable.
  add_library(${targetName} SHARED ${projectSources})
else()
  add_executable(${targetName} ${projectSources})
endif()

target_link_libraries(${targetName}
  ${SDL2MAIN_LIBRARY}
  ${SDL2_LIBRARY}
  ${OPENGL_LIBRARY}
  ${GLAD_LIBRARY}
  ${SPDLOG_LIBRARY}
  # ${IMGUI_LIBRARY}
  ${IMGUI_DOCKING}
)

target_include_directories(${targetName}
  PUBLIC ${projectIncludeDirs}
)


