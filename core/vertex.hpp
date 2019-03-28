#pragma once
#include "math.hpp"

struct Vertex {
    Vertex(const glm::vec3& _pos, const glm::vec2& _texc, const glm::vec3& _nor, const glm::vec4& _colr=glm::vec4(1.0))
        : position(_pos), texcoord(_texc), normal(_nor), color(_colr) {

    }
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
    glm::vec4 color;
};
