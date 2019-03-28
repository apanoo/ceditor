#pragma once

#include "util.h"

enum BufferType {
    VBO = GL_ARRAY_BUFFER,
    EBO = GL_ELEMENT_ARRAY_BUFFER,
};

// VBO & EBO
class ArrayBuffer {
public:
    ArrayBuffer(BufferType type, GLsizei count, void* data) 
        : _bufType(type), _count(count) {
        glGenBuffers(1, &_bufID);
        glBindBuffer(_bufType, _bufID);
        glBufferData(_bufType, count, data, GL_STATIC_DRAW);
        glBindBuffer(_bufType, 0);
    }
    virtual ~ArrayBuffer() {
        glDeleteBuffers(1, &_bufID);
    }

    void bind() {
        glBindBuffer(_bufType, _bufID);
    }

    void unbind() {
        glBindBuffer(_bufType, 0);
    }

    inline GLsizei getCount() const { return _count; }

private:
    BufferType _bufType;
    GLuint _bufID;
    GLsizei _count;
};