// don't listen to MS complains, we want cross-platform code
#define _CRT_SECURE_NO_DEPRECATE

// C++
//#include <filesystem>
#include <vector>
// SDL
#include "core/util.h"
// Dear ImGui
#include "2d/gui/imgui-style.h"
#include "2d/gui/imgui_impl_opengl3.h"
#include "2d/gui/imgui_impl_sdl.h"
#include "imgui.h"

#include "2d/gui/functions.h"

SDL_Window *window;

// the function called by the javascript code
#ifdef EMSCRIPTEN
void __reset_window() {
  int __width = EM_ASM_INT({ return window.innerWidth; });
  int __height = EM_ASM_INT({ return window.innerHeight; });

  std::cout << "set width from web: " << __width << std::endl;
  std::cout << "set height from web: " << __height << std::endl;

  // reset window
  SDL_SetWindowSize(window, __width, __height);
}

extern "C" void EMSCRIPTEN_KEEPALIVE set_window_size() {
  // get size from js
  __reset_window();

  // reset window size

  // SDL_SetWindowSize(window, w, h);
  // std::cout << "set window size from web" << std::endl;
}
std::function<void()> loopf;
void main_loop() { loopf(); }
#endif // EMSCRIPTEN

int windowWidth = 1280, windowHeight = 720;

int main(int argc, char *argv[]) {
  std::cout << "[" << currentTime(std::chrono::system_clock::now()) << "] "
            << "Start\n- - -\n\n";
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  std::string glsl_version = "#version 100";

  // #ifdef EMSCRIPTEN
  //   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  //   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  //   SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window,
  //   nullptr);
  // #else
  // initiate SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("[ERROR] %s\n", SDL_GetError());
    return -1;
  }

#ifdef EMSCRIPTEN
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

#ifdef __APPLE__
  // GL 3.2 Core + GLSL 150
  glsl_version = "#version 150";
  SDL_GL_SetAttribute( // required on Mac OS
      SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#elif __linux__
  // GL 3.2 Core + GLSL 150
  glsl_version = "#version 150";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#elif _WIN32
  // GL 3.0 + GLSL 130
  glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#endif

  SDL_WindowFlags window_flags = (SDL_WindowFlags)(
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow("Dear ImGui SDL", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                            window_flags);
  // limit to which minimum size user can resize the window
  // SDL_SetWindowMinimumSize(window, 500, 300);

  SDL_version compiled;
  SDL_VERSION(&compiled);
  std::ostringstream compiledVal;
  compiledVal << "Compiled with " << std::to_string(compiled.major) << "."
              << std::to_string(compiled.minor) << "."
              << std::to_string(compiled.patch);

  SDL_version linked;
  SDL_GetVersion(&linked);
  std::ostringstream linkedVal;
  linkedVal << "Linked with " << std::to_string(linked.major) << "."
            << std::to_string(linked.minor) << "."
            << std::to_string(linked.patch);

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);

  // enable VSync
  SDL_GL_SetSwapInterval(1);

#if defined(__ANDROID__) || defined(EMSCRIPTEN) || defined(__IPHONEOS__)
  // no glad on android/web/iOS

  // int __width = EM_ASM_INT({ return window.innerWidth; });
  // int __height = EM_ASM_INT({ return window.innerHeight; });

  // std::cout << "set width from web: " << __width << std::endl;
  // std::cout << "set height from web: " << __height << std::endl;

  // // reset window
  // SDL_SetWindowSize(window, __width, __height);
  __reset_window();

#else
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "[ERROR] Couldn't initialize glad" << std::endl;
  } else {
    std::cout << "[INFO] glad initialized\n";
  }
  std::cout << "[INFO] OpenGL renderer: " << glGetString(GL_RENDERER)
            << std::endl;

  // apparently, that shows maximum supported version
  std::cout << "[INFO] OpenGL from glad: " << GLVersion.major << "."
            << GLVersion.minor << std::endl;
  glViewport(0, 0, windowWidth, windowHeight);

#endif

  // setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.IniFilename = "assets/imgui.ini";
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable
  io.Fonts->AddFontFromFileTTF("assets/fonts/verdana.ttf", 15.0f, NULL, NULL);

  setImGuiStyle();

  // setup platform/renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version.c_str());

  // colors are set in RGBA, but as float
  ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);

  glClearColor(background.x, background.y, background.z, background.w);
  // --- rendering loop

  bool loop = true;
#ifdef EMSCRIPTEN
  loopf = [&] {
#else
  while (loop) {
#endif
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      // without it you won't have keyboard input and other things
      ImGui_ImplSDL2_ProcessEvent(&event);
      // you might also want to check io.WantCaptureMouse and
      // io.WantCaptureKeyboard before processing events

      switch (event.type) {
      case SDL_QUIT:
        loop = false;
        break;

      case SDL_WINDOWEVENT:
        switch (event.window.event) {
        case SDL_WINDOWEVENT_RESIZED: // not support for web
          windowWidth = event.window.data1;
          windowHeight = event.window.data2;
          glViewport(0, 0, windowWidth, windowHeight);
          break;
        }
        break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          loop = false;
          break;
        }
        break;
      }
    }

    // start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    // standard demo window
    bool demo = true;
    ImGui::ShowDemoWindow(&demo);

    // rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
#ifdef EMSCRIPTEN
  };
  emscripten_set_main_loop(main_loop, 0, true);
#else
  }
#endif

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "\n- - -\n"
            << "[" << currentTime(std::chrono::system_clock::now()) << "] "
            << "Quit\n";

  return 0;
}
