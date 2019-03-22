#pragma once

#include <string>
#include <iostream>
#include <SDL.h>
// #include <SDL_opengl_glext.h>

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

// debug check OpenGL error
GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
#if !defined(__ANDROID__) && !defined(__IPHONEOS__) && !defined(EMSCRIPTEN)
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
#endif
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }

        SDL_Log("%d %s | %s (%d)", errorCode, error.c_str(), file, line);
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 