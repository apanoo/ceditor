#pragma once

#include <string>
#include <iostream>
#include <SDL.h>

#ifdef EMSCRIPTEN
#include <functional>
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#else
// glad
#include <glad/glad.h>
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