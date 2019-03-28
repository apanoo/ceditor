#pragma once

#include <deque>
#include "2d/renderable.hpp"

class Renderer {
public:
    Renderer() = default;
    virtual ~Renderer() {}
public:
    virtual void submit(const Renderable *renderable) = 0;
    virtual void flush() {}
};

// simple renderer
class SimpleRenderer : public Renderer {
public:
    void submit(const Renderable *renderable) override {
        _renderables.push_back(renderable);
    }

    void flush() override {
        while(!_renderables.empty()) {
            const Renderable* renderable = _renderables.front();
            renderable->getVBO()->bind();
            ArrayBuffer *ebo = renderable->getEBO();
            ebo->bind();
            
            // move object to it's position
            renderable->getShader()->setUniformMat4("M", glm::translate(glm::mat4(1), renderable->getPosition()));
            glDrawElements(GL_TRIANGLES, ebo->getCount(), GL_UNSIGNED_INT, 0);

            ebo->unbind();

            renderable->getEBO()->unbind();
            renderable->getVBO()->unbind();

            _renderables.pop_front();
        }
    }

private:
    std::deque<const Renderable*> _renderables;
};