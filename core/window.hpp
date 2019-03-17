#include <vector>
#include "util.h"
#include "sprite.hpp"

// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position;                     \n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_Position = vec4(position.xyz, 1.0);     \n"
    "}                                            \n";
const GLchar* fragmentSource =
    "void main()                                  \n"
    "{                                            \n"
    "  gl_FragColor[0] = gl_FragCoord.x/640.0;    \n"
    "  gl_FragColor[1] = gl_FragCoord.y/480.0;    \n"
    "  gl_FragColor[2] = 0.5;                     \n"
    "}                                            \n";
GLfloat vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};

class Window {
public:
    Window(const std::string &title, int w, int h, int sx = 0, int sy = 0) :
        _title(title), _width(w), _height(h), _startx(sx), _starty(sy), _quit(false), _bgblack(true) {
        init();
        flags = SDL_WINDOW_OPENGL;
#if defined(__ANDROID__)
        flags |= SDL_WINDOW_FULLSCREEN;
#endif
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

        // update shader 
        // move a vertex
        const uint32_t milliseconds_since_start = SDL_GetTicks();
        const uint32_t milliseconds_per_loop = 3000;
        vertices[0] = ( milliseconds_since_start % milliseconds_per_loop ) / float(milliseconds_per_loop) - 0.5f;
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Clear the screen
        if( _bgblack )
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        else
            glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLenum error = glGetError();
        if ( error != GL_NO_ERROR ) {
            // TODO logger...
            std::cout << "OpenGL error: " << error << std::endl;
            // exit(-1);
        }

        // sp.draw();

        // Draw a triangle from the 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);
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

#ifndef __ANDROID__
        // Load OpenGL functions glad SDL
        gladLoadGLLoader(SDL_GL_GetProcAddress);
#endif

        // V-Sync
        SDL_GL_SetSwapInterval(1);

        // set viewport
        GLint vpWidth, vpHeight;
        SDL_GL_GetDrawableSize(_sdl_window, &vpWidth, &vpHeight);
        glViewport(0, 0, vpWidth, vpHeight);

        // sp.init(-1.0f, -1.0f, 1.0f, 1.0f);
    #endif

    // shader 
    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // get compile result
    GLint result;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &result );
    if ( result == GL_FALSE ) {
        GLint length;
        glGetShaderiv( vertexShader, GL_INFO_LOG_LENGTH, &length );
        std::vector<char> error(length);
        // get compile errors
        glGetShaderInfoLog( vertexShader, length, &length, &error[ 0 ] );
        //aplog::logerr( "Error to compile vert shader!", &error[ 0 ] );
		std::cout << "Error to compile vert shader: " << &error[0] << std::endl;
        exit(-1);
    }

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &result );
    if ( result == GL_FALSE ) {
        GLint length;
        glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &length );
        std::vector< char > error( length );
        // get compile errors
        glGetShaderInfoLog( fragmentShader, length, &length, &error[ 0 ] );
        //aplog::logerr( "Error to compile frag shader!", &error[ 0 ] );
		std::cout << "Error to compile frag shader: " << &error[0] << std::endl;
        glDeleteShader( fragmentShader );
        exit(-1);
    }

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Delete shader data
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
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
    Sprite sp;

    Uint32 flags;
};