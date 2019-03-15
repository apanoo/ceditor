//
// Created by apanoo on 3/15/19.
//
#include <jni.h>

#include "helper.hpp"

GLint	g_programObject;
jint	g_width;
jint	g_height;

#ifndef CEDITOR_RENDERER_H
#define CEDITOR_RENDERER_H

extern "C"
JNIEXPORT void JNICALL
Java_cn_apanoo_ceditor_RendererJNI_glesInit(JNIEnv *env, jobject instance) {

    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                            \n";

//    char *pVertexShader = readShaderSrcFile("shader/vs.glsl", g_pAssetManager);
//    char *pFragmentShader = readShaderSrcFile("shader/fs.glsl", g_pAssetManager);

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader ( GL_VERTEX_SHADER, vShaderStr );
    fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fShaderStr );
//    vertexShader = LoadShader ( GL_VERTEX_SHADER, pVertexShader );
//    fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, pFragmentShader );

    // Create the program object
    programObject = glCreateProgram ( );

    if ( programObject == 0 )
    {
        return;
    }

    glAttachShader ( programObject, vertexShader );
    glAttachShader ( programObject, fragmentShader );

    // Link the program
    glLinkProgram ( programObject );

    // Check the link status
    glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

    if ( !linked )
    {
        GLint infoLen = 0;

        glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );

        if ( infoLen > 1 )
        {
            char *infoLog = (char *)malloc ( sizeof ( char ) * infoLen );

            glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
            LOGE("Error linking program:[%s]", infoLog );

            free ( infoLog );
        }

        glDeleteProgram ( programObject );
        return;
    }

    // Store the program object
    g_programObject = programObject;

    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );

}extern "C"
JNIEXPORT void JNICALL
Java_cn_apanoo_ceditor_RendererJNI_glesRender(JNIEnv *env, jobject instance) {

    GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f,
                             -0.5f, -0.5f, 0.0f,
                             0.5f, -0.5f, 0.0f
    };

    // Set the viewport
    glViewport ( 0, 0, g_width, g_height );

    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT );

    // Use the program object
    glUseProgram ( g_programObject );

    // Load the vertex data
    glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray ( 0 );

    glDrawArrays ( GL_TRIANGLES, 0, 3 );

}extern "C"
JNIEXPORT void JNICALL
Java_cn_apanoo_ceditor_RendererJNI_glesResize(JNIEnv *env, jobject instance, jint width,
jint height) {

    g_width = width;
    g_height = height;

}extern "C"
JNIEXPORT void JNICALL
Java_cn_apanoo_ceditor_RendererJNI_readShaderFile(JNIEnv *env, jobject instance, jobject assetMgr) {

    if (assetMgr && env)
    {
        //LOGI("before AAssetManager_fromJava");
        g_pAssetManager = AAssetManager_fromJava(env, assetMgr);
        //LOGI("after AAssetManager_fromJava");
        if (NULL == g_pAssetManager)
        {
            LOGE("AAssetManager_fromJava() return null !");
        }
    }
    else
    {
        LOGE("assetManager is null !");
    }

}

#endif //CEDITOR_RENDERER_H
