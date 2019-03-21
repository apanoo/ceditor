#pragma once

#include <string>
#include <iostream>
#include <SDL.h>

// android or wasm
#if defined(__ANDROID__) || defined(EMSCRIPTEN) || defined(__IPHONEOS__)
   #include <SDL_opengles2.h>
#endif

// wasm
#ifdef EMSCRIPTEN
#include <functional>
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES 1
#else
#if defined(__ANDROID__) || defined(__IPHONEOS__)
// no glad on android/iOS
#else
// glad on Linux/Win/Mac
#include <glad/glad.h>
#endif
#endif // EMEMSCRIPTEN
