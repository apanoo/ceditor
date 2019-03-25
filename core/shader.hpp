#pragma once
#include <vector>
#include <iostream>
#include "util.h"
#include "math.hpp"
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

    GLuint getAttribLocation(const GLchar* name) {
        return glGetAttribLocation(_shader, name);
    }

    ///// set uniform /////
    void setUniform1f(const GLchar* name, float value) {
        glUniform1f(getUniformLocation(name), value);
    }

    void setUniform1i(const GLchar* name, int value) {
        glUniform1i(getUniformLocation(name), value);
    }

    void setUniform2f(const GLchar* name, const glm::vec2& vector) {
        glUniform2f(getUniformLocation(name), vector.x, vector.y);
    }

    void setUniform3f(const GLchar* name, const glm::vec3& vector) {
        glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
    }

    void setUniform4f(const GLchar* name, const glm::vec4& vector) {
        glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
    }

    void setUniformMat4(const GLchar* name, const glm::mat4& matrix) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    ///// !set uniform /////

    void enable() const {
        glUseProgram(_shader);
    }

    void disable() const {
        glUseProgram(0);
    }
private:
    GLuint getUniformLocation(const GLchar* name) {
        return glGetUniformLocation(_shader, name);
    }

    /**
     *  internal load shader from file
     *  and compile & link
     **/
    GLuint load() {
        GLuint program = glCreateProgram();

        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

        // source
        const char* vsource = (const char*)FileUtils::read_raw(_vert);
        const char* fsource = (const char*)FileUtils::read_raw(_frag);
        
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
            SDL_Log("Vertex shader error: %s", &error[0]);
            // std::cout << "Vertex: " << &error[0] << std::endl;
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
            SDL_Log("Fragment shader error: %s", &error[0]);
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

        FileUtils::free_raw((unsigned char*)vsource);
        FileUtils::free_raw((unsigned char*)fsource);

        return program;
    }

private:
    GLuint _shader;
    const char *_vert;
    const char *_frag;
};