#pragma once
#include "util.h"

class Sprite {
public:
    Sprite() : _vboID(0) {

    }
    ~Sprite() {
        if (_vboID != 0) {
            glDeleteBuffers(1, &_vboID);
        }
    }
public:
    void draw() {
        // bind buffer to draw
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);  // 6 vertex

        glDisableVertexAttribArray(0);

        // unbind after draw
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

public:
    void init(float x, float y, float w, float h) {
        _x = x;
        _y = y;
        _h = h;
        _w = w;

        // gen id
        if (_vboID == 0) {
            glGenBuffers(1, &_vboID);
        }
        // 6 points , 2 : x/y => 6 * 2 = 12
        float vertexData[12];

        // first triangle
        // right & up
        vertexData[0] = x + _w;
        vertexData[1] = y + _h;

        // left & up
        vertexData[2] = x;
        vertexData[3] = y + _h;

        // left & down
        vertexData[4] = x;
        vertexData[5] = y;

        // second triangle
        // left & down
        vertexData[0] = x;
        vertexData[1] = y;

        // right & down
        vertexData[2] = x + _w;
        vertexData[3] = y;

        // right & up
        vertexData[4] = x + _w;
        vertexData[5] = y + _h;

        // upload data
        // bind
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        glBufferData(GL_ARRAY_BUFFER, 
            sizeof(vertexData),
            vertexData, GL_STATIC_DRAW);
        
        // unbind buffer to draw nothing
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
private:
    float _x;
    float _y;
    float _w;
    float _h;

    GLuint _vboID;
};