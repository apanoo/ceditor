#include <vector>
#include <string>
#include "util.h"
#include "shader.hpp"
#include "sprite.hpp"
#include "math.hpp"
#include "vertex.hpp"
#include "buffer.hpp"
#include "model.hpp"

Shader *shader;

ArrayBuffer *_vbo;
ArrayBuffer *_ebo;

OBJModel *model;

glm::mat4 vmdl = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, -5.0f)) *
    glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0)) *
    glm::scale(glm::mat4(1), glm::vec3(0.002f, 0.002f, 0.002f)); // bunny scale

glm::mat4 normalMatrix = glm::inverseTranspose(vmdl);

GLint lp ;
GLint tc ;
GLint nr ;
GLint mp ;
GLint vp ;
GLint pp ;
GLint nm ;

class Window {
public:
    Window(const std::string &title, int w, int h, int sx = 0, int sy = 0) :
        _title(title), _width(w), _height(h), _startx(sx), _starty(sy), _quit(false), _bgblack(true) {
        flags = SDL_WINDOW_OPENGL;
#if defined(__ANDROID__) || defined(__IPHONEOS__)
        flags |= SDL_WINDOW_FULLSCREEN;
#endif
#if defined(__IPHONEOS__)
        flags |= SDL_WINDOW_ALLOW_HIGHDPI;
#endif
        // init window after init flags
        init();

        // test shader
        shader = new Shader("assets/shader/specular.vert", "assets/shader/specular.frag");
        model = new OBJModel("assets/models/bunny.obj");

        _vbo = new ArrayBuffer(BufferType::VBO, sizeof(Vertex) * model->_vertices.size(), &model->_vertices[0]);
        _vbo->bind();

        _ebo = new ArrayBuffer(BufferType::EBO, sizeof(unsigned int)*model->_indices.size(), &model->_indices[0]);
        _ebo->bind();

        lp = shader->getAttribLocation("position");
        tc = shader->getAttribLocation("texcoord");
        nr = shader->getAttribLocation("normal");

        mp = shader->getUniformLocation("M");
        vp = shader->getUniformLocation("V");
        pp = shader->getUniformLocation("P");
        nm = shader->getUniformLocation("NM");

        SDL_Log("lp: %d, tc: %d, nr: %d, mp: %d, vp: %d, pp: %d", lp, tc, nr, mp, vp, pp);

        glEnableVertexAttribArray(lp);
        glVertexAttribPointer(lp, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(tc);
        glVertexAttribPointer(tc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*3));

        glEnableVertexAttribArray(nr);
        glVertexAttribPointer(nr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*5));

        // unbind vbo & ebo
        _vbo->unbind();
        _ebo->unbind();
    }

    ~Window() {
        SDL_GL_DeleteContext(_glContext);
        SDL_DestroyWindow(_sdl_window);

        delete _vbo;
        delete _ebo;
        delete model;
    }

public:
    bool isQuit() const { return _quit; }
    
    void togglebg() { _bgblack = !_bgblack; }

    void update() {
        SDL_GL_SwapWindow(_sdl_window);

        // event loop
        while(SDL_PollEvent(&_event)) {
            if(_event.type == SDL_QUIT) {
                _quit = true;
            }
        }

        // Clear the screen
        if(_bgblack)
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        else
            glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        // show 3D model should clear depth bit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // check error and pause
        glCheckError();

        render();
    }

    void render() {
        shader->enable();

        glUniformMatrix4fv(mp, 1, GL_FALSE, glm::value_ptr(vmdl));
        glUniformMatrix4fv(vp, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
        glUniformMatrix4fv(pp, 1, GL_FALSE, glm::value_ptr(glm::perspective(45.0f, 680.0f / 480.0f, 0.1f, 1000.0f)));
        glUniformMatrix4fv(nm, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        _ebo->bind();
        glDrawElements(GL_TRIANGLES, model->_indices.size(), GL_UNSIGNED_INT, 0);
        _ebo->unbind();
        
        shader->disable();
    }

private:
    void init() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    #ifdef EMSCRIPTEN
        SDL_CreateWindowAndRenderer(_width, _height, 0, &_sdl_window, nullptr);
    #else
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            SDL_Log("Could not initialize SDL");
        }
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        _sdl_window = SDL_CreateWindow(_title.c_str(), 
                _startx != 0 ? _startx : SDL_WINDOWPOS_CENTERED,
                _starty != 0 ? _starty : SDL_WINDOWPOS_CENTERED,
                _width,
                _height,
                flags);

        if(_sdl_window == NULL) {
            SDL_Log("Could not create window");
        }
        _glContext = SDL_GL_CreateContext(_sdl_window);
        if(_glContext == NULL) {
            SDL_Log("Could not create the OpenGL context");
        }

#if defined(__ANDROID__) || defined(EMSCRIPTEN) || defined(__IPHONEOS__)
        // no glad on android/web/iOS
#else
        gladLoadGLLoader(SDL_GL_GetProcAddress);
#endif
        SDL_Log("OpenGL : %s", glGetString(GL_VERSION));

        // V-Sync
        SDL_GL_SetSwapInterval(1);

        // set viewport
        GLint vpWidth, vpHeight;
        SDL_GL_GetDrawableSize(_sdl_window, &vpWidth, &vpHeight);
        glViewport(0, 0, vpWidth, vpHeight);

#endif
        // show 3D model should enable depth test
        glEnable(GL_DEPTH_TEST);
    }
private:
    SDL_Window *_sdl_window;
    SDL_GLContext _glContext;
    SDL_Event _event;
    std::string _title;
    int _width;
    int _height;
    int _startx;
    int _starty;
    bool _quit;
    bool _bgblack;

    Uint32 flags;
};