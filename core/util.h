#pragma once

#include <string>
#include <iostream>
#include <SDL.h>

// android or wasm
#if defined(__ANDROID__) || defined(EMSCRIPTEN)
   #include <SDL_opengles2.h>
#endif

// wasm
#ifdef EMSCRIPTEN
#include <functional>
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES 1
#else
#ifndef __ANDROID__
// glad on Linux/Win/Mac
#include <glad/glad.h>
#endif
#endif // EMEMSCRIPTEN

/// simple helper
void __stdlog (const std::string &msg) {
    std::cout << msg << std::endl;
}

void __stderr (const std::string &msg) {
    __stdlog(msg);
}

void __fatal(const std::string &msg) {
    __stderr(msg);
    int wait;
    std::cin >> wait;
    exit(-1);  // exit system
}