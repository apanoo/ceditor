#pragma once
#include <vector>
#include <iostream>
#include "util.h"
#include "file.hpp"

class Shader {
public:
    /**
     * vert: vertex shader path
     * frag: fragment shader path
     **/
    Shader(const char* vert, const char* frag)
        :_vert(vert), _frag(frag) {
        _shader = load();
    }
    ~Shader() {
        glDeleteProgram(_shader);
    }

    GLuint getAttribLocation(const char* name) {
        return glGetAttribLocation(_shader, name);
    }

    GLuint getUniformLocation(const char* name) {
        return glGetUniformLocation(_shader, name);
    }

    void enable() const {
        glUseProgram(_shader);
    }

    void disable() const {
        glUseProgram(0);
    }
private:
    /**
     *  internal load shader from file
     *  and compile & link
     **/
    GLuint load() {
        GLuint program = glCreateProgram();

        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

        // source
        std::string vss = FileUtils::read(_vert);
        std::string fss = FileUtils::read(_frag);
        const char* vsource = vss.c_str();
        const char* fsource = fss.c_str();
        // set source
        glShaderSource(vertex, 1, &vsource, NULL);
        glCompileShader(vertex);
        // get compile error
        GLint result;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertex, length, &length, &error[0]);
            // delete
            glDeleteShader(vertex);
            std::cout << "Vertex: " << &error[0] << std::endl;
            return 0;
        }

        glShaderSource(fragment, 1, &fsource, NULL);
        glCompileShader(fragment);
        // get fragment compile error
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragment, length, &length, &error[0]);
            // delete
            glDeleteShader(fragment);
            std::cout << "Fragment: " << &error[0] << std::endl;
            return 0;
        }
        // attach shader
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        // link & validate
        glLinkProgram(program);
        glValidateProgram(program);
        // detach shader
        glDetachShader(program, vertex);
        glDetachShader(program, fragment);

        // delete data
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }

private:
    GLuint _shader;
    const char *_vert;
    const char *_frag;
};