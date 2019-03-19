#include <vector>
#include <string>
#include "util.h"
#include "shader.hpp"
#include "sprite.hpp"
#include "math.hpp"
#include "vertex.hpp"

Shader *shader;
Vertex vertices[3];

GLuint vbo;

GLint lp ;
GLint cp ;
GLint mp ;
GLint vp ;
GLint pp ;

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
        vertices[0].position[0] = 0;
        vertices[0].position[1] = 0;
        vertices[0].position[2] = -100.0f;
        vertices[0].color[0] = 1.0f;
        vertices[0].color[1] = 1.0f;
        vertices[0].color[2] = 1.0f;
        vertices[0].color[3] = 1.0f;

        vertices[1].position[0] = 10;
        vertices[1].position[1] = 0;
        vertices[1].position[2] = -100.0f;
        vertices[1].color[0] = 1.0f;
        vertices[1].color[1] = 1.0f;
        vertices[1].color[2] = 1.0f;
        vertices[1].color[3] = 1.0f;

        vertices[2].position[0] = 0;
        vertices[2].position[1] = 10;
        vertices[2].position[2] = -100.0f;
        vertices[2].color[0] = 1.0f;
        vertices[2].color[1] = 1.0f;
        vertices[2].color[2] = 1.0f;
        vertices[2].color[3] = 1.0f;

        // test shader
        shader = new Shader("assets/shader/sample.vert", "assets/shader/sample.frag");

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, vertices, GL_STATIC_DRAW);

        lp = shader->getAttribLocation("position");
        cp = shader->getAttribLocation("color");
        mp = shader->getUniformLocation("M");
        vp = shader->getUniformLocation("V");
        pp = shader->getUniformLocation("P");

        SDL_Log("lp: %d, cp: %d, mp: %d, vp: %d, pp: %d", lp, cp, mp, vp, pp);

        glEnableVertexAttribArray(lp);
        glVertexAttribPointer(lp, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(cp);
        glVertexAttribPointer(cp, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*3));
    }

    ~Window() {
        SDL_GL_DeleteContext(_glContext);
        SDL_DestroyWindow(_sdl_window);
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
        if( _bgblack )
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        else
            glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLenum error = glGetError();
        if ( error != GL_NO_ERROR ) {
            std::cout << "OpenGL error : " << error << std::endl;
            // exit(-1);
        }
        render();
    }

    void render() {
        shader->enable();

        glUniformMatrix4fv(mp, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
        glUniformMatrix4fv(vp, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
        glUniformMatrix4fv(pp, 1, GL_FALSE, glm::value_ptr(glm::perspective(45.0f, 680.0f / 480.0f, 0.1f, 1000.0f)));

        glDrawArrays(GL_TRIANGLES, 0, 6);
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
            std::cout << "Could not initialize SDL" << std::endl;
        }
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        _sdl_window = SDL_CreateWindow(_title.c_str(), 
                _startx != 0 ? _startx : SDL_WINDOWPOS_CENTERED,
                _starty != 0 ? _starty : SDL_WINDOWPOS_CENTERED,
                _width,
                _height,
                flags);

        if(_sdl_window == NULL) {
            std::cout << "Could not create window" << std::endl;
        }
        _glContext = SDL_GL_CreateContext(_sdl_window);
        if(_glContext == NULL) {
            std::cout << "Could not create the OpenGL context" << std::endl;
        }

#if defined(__ANDROID__) || defined(EMSCRIPTEN) || defined(__IPHONEOS__)
        // no glad on android/web/iOS
#else
        gladLoadGLLoader(SDL_GL_GetProcAddress);
#endif

        std::cout << "OpenGL :" << glGetString( GL_VERSION ) << std::endl;

        // V-Sync
        SDL_GL_SetSwapInterval(1);

        // set viewport
        GLint vpWidth, vpHeight;
        SDL_GL_GetDrawableSize(_sdl_window, &vpWidth, &vpHeight);
        glViewport(0, 0, vpWidth, vpHeight);

    #endif
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