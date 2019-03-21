#pragma once
#include "math.hpp"

struct Vertex {
    Vertex(const glm::vec3& _pos, const glm::vec2& _texc, const glm::vec3& _nor)
        : position(_pos), texcoord(_texc), normal(_nor) {

    }
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};
