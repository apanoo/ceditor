/* Freetype GL - A C OpenGL Freetype engine
 *
 * Distributed under the OSI-approved BSD 2-Clause License.  See accompanying
 * file `LICENSE` for more details.
 */
#ifndef __OPEN_GL_H__
#define __OPEN_GL_H__

#if defined(__APPLE__)
#   include "TargetConditionals.h"
#   if TARGET_OS_SIMULATOR || TARGET_OS_IPHONE  // iOS
#     if defined(FREETYPE_GL_ES_VERSION_3_0)
#       include <OpenGLES/ES3/gl.h>
#     else
#       include <OpenGLES/ES2/gl.h>
#     endif
#   else
#     include <glad/glad.h> // mac
#   endif
#elif defined(_WIN32) || defined(_WIN64)
#  include <glad/glad.h>      // winodws
#elif defined(__ANDROID__)
#  include <GLES3/gl3.h>    // android
#else 
#  include <glad/glad.h>      // linux
#endif

#endif /* OPEN_GL_H */
