#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi

#include <iostream>

void test_math() {
    // vec2
    glm::vec2 v2 = glm::vec2(1.0f, 2.0f);
    std::cout << "===vec2=== " << v2.x << " " << v2.y << std::endl;

    // vec3
    glm::vec3 v3 = glm::vec3(1.0f, 2.0f, 3.0f);
    std::cout << "===vec3=== " << v3.x << " " << v3.y << " " << v3.z << std::endl;

    // vec4
    glm::vec4 v4 = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
    std::cout << "===vec4=== " << v4.x << " " << v4.y << " " << v4.z << " " << v4.w << std::endl;

    // mat3

    // mat4

    // ...
}