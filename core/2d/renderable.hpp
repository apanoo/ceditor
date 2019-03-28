#pragma once

#include <vector>
#include "shader.hpp"
#include "math.hpp"
#include "vertex.hpp"
#include "buffer.hpp"

class Renderable {
public:
    Renderable(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader *shader)
        :_position(position), _size(size), _color(color), _shader(shader) {
            std::vector<Vertex> vertices;
            calVertex(vertices);

            std::vector<unsigned int> indices;
            calIndex(indices);

            // vertex
            _vbo = new ArrayBuffer(BufferType::VBO, sizeof(Vertex) * vertices.size(), &vertices[0]);
            _vbo->bind();
            // index
            _ebo = new ArrayBuffer(BufferType::EBO, sizeof(unsigned int) * indices.size(), &indices[0]);
            _ebo->bind();
            // buffer data
            GLint lp = shader->getAttribLocation("position");
            // GLint tc= shader->getAttribLocation("texcoord");
            // GLint nr= shader->getAttribLocation("normal");
            GLint cl= shader->getAttribLocation("color");

            glEnableVertexAttribArray(lp);
            glVertexAttribPointer(lp, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

            // glEnableVertexAttribArray(tc);
            // glVertexAttribPointer(tc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*3));

            // glEnableVertexAttribArray(nr);
            // glVertexAttribPointer(nr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*5));

            glEnableVertexAttribArray(cl);
            glVertexAttribPointer(cl, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*8));

            // unbind
            _ebo->unbind();
            _vbo->unbind();
        }

        virtual ~Renderable() {
            delete _ebo;
            delete _vbo;
        }
public:
    inline const glm::vec3& getPosition() const { return _position; }
    inline const glm::vec2& getSize() const { return _size; }
    inline const glm::vec4& getColor() const { return _color; }
    inline ArrayBuffer* getEBO() const { return _ebo; }
    inline ArrayBuffer* getVBO() const { return _vbo; }

    inline Shader* getShader() const { return _shader; }

private:
    void calIndex(std::vector<unsigned int> &is) {
        is.push_back(0);
        is.push_back(1);
        is.push_back(2);
        is.push_back(2);
        is.push_back(3);
        is.push_back(0);
    }

    void calVertex(std::vector<Vertex> &vs) {
        vs.push_back(
            Vertex(
                glm::vec3(0, 0, 0),// vertex
                glm::vec2(0, 0),
                glm::vec3(0, 0, 0),
                glm::vec4(_color.x, _color.y, _color.z, _color.w) // color
            )
        );
        vs.push_back(
            Vertex(
                glm::vec3(0, _size.y, 0),// vertex
                glm::vec2(0, 0),
                glm::vec3(0, 0, 0),
                glm::vec4(_color.x, _color.y, _color.z, _color.w) // color
            )
        );
        vs.push_back(
            Vertex(
                glm::vec3(_size.x, _size.y, 0),// vertex
                glm::vec2(0, 0),
                glm::vec3(0, 0, 0),
                glm::vec4(_color.x, _color.y, _color.z, _color.w) // color
            )
        );
        vs.push_back(
            Vertex(
                glm::vec3(_size.x, 0, 0),// vertex
                glm::vec2(0, 0),
                glm::vec3(0, 0, 0),
                glm::vec4(_color.x, _color.y, _color.z, _color.w) // color
            )
        );
    }

protected:
    glm::vec3 _position;
    glm::vec2 _size;
    glm::vec4 _color;

    ArrayBuffer *_ebo;
    ArrayBuffer *_vbo;

    Shader *_shader;
};