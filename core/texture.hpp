#pragma once
#include <string>
#include "util.h"
#include "file.hpp"

class Texture {
public:
    Texture(const char* filepath) : _filepath(filepath) {
        _texture = load(filepath);
    }
    virtual ~Texture() {
    }

public:
    void bind() {
        glBindTexture(GL_TEXTURE_2D, _texture);
    }

    void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

private:
    GLuint load(const char* filepath) {
        if (std::string(filepath).empty()) {
            SDL_Log("Filepath should not be empty");
            return 0;
        }
        
        GLuint texture;
        glGenTextures(1, &texture);
        // active texture unit 0
        glActiveTexture(GL_TEXTURE0);
        // bind texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // read image data
        unsigned char* data = FileUtils::read_image(_filepath.c_str(), &_image_width, &_image_height, &_image_channls);
        if (data) {
            // set image data to GPU sampler unit
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image_width, _image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // gen mipmap
            // glGenerateMipmap(GL_TEXTURE_2D); // crash
        } else {
            SDL_Log("Failed to load texture [%s]", _filepath.c_str());
        }

        // free image data
        FileUtils::release_image(data);
        
        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
        return texture;
    }

private:
    GLuint _texture;
    int _image_width;
    int _image_height;
    int _image_channls;     // rgb: 3 / rgba: 4 / ...
    std::string _filepath;
};