// don't listen to MS complains, we want cross-platform code
#define _CRT_SECURE_NO_DEPRECATE

// C++
//#include <filesystem>
#include <vector>
// SDL
#include <SDL.h>
#include <glad/glad.h>
// Dear ImGui
#include "2d/gui/imgui-style.h"
#include "2d/gui/imgui_impl_opengl3.h"
#include "2d/gui/imgui_impl_sdl.h"
#include "imgui.h"

#include "2d/gui/functions.h"

// dialog ext
#include "editor/ext/portable-file-dialogs.h"

// tray ext
// #include "tray.h"

int windowWidth = 1280, windowHeight = 720;

int main(int argc, char *argv[]) {
  std::cout << "[" << currentTime(std::chrono::system_clock::now()) << "] "
            << "Start\n- - -\n\n";

  // std::vector<std::string> files;
  // auto currentPath = std::filesystem::current_path();
  // //std::cout << currentPath.string();
  // for (const auto &entry : std::filesystem::directory_iterator(currentPath))
  // {
  //     files.push_back(entry.path().filename().string().data());
  //     //std::cout << entry.path().filename() << std::endl;
  // }

  // initiate SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("[ERROR] %s\n", SDL_GetError());
    return -1;
  }

  SDL_version compiled;
  SDL_VERSION(&compiled);
  std::ostringstream compiledVal;
  compiledVal << "Compiled with " << std::to_string(compiled.major) << "."
              << std::to_string(compiled.minor) << "."
              << std::to_string(compiled.patch);
  // std::cout << compiledVal.str() << std::endl;

  SDL_version linked;
  SDL_GetVersion(&linked);
  std::ostringstream linkedVal;
  linkedVal << "Linked with " << std::to_string(linked.major) << "."
            << std::to_string(linked.minor) << "."
            << std::to_string(linked.patch);
  // std::cout << linkedVal.str() << std::endl;

  // setup SDL window

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  std::string glsl_version = "";
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
  SDL_Window *window = SDL_CreateWindow(
      "Dear ImGui SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      windowWidth, windowHeight, window_flags);
  // limit to which minimum size user can resize the window
  SDL_SetWindowMinimumSize(window, 500, 300);

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);

  // enable VSync
  SDL_GL_SetSwapInterval(1);

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

  // int sdlOpenGLmajor = 0,
  //     sdlOpenGLminor = 0;
  // SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &sdlOpenGLmajor);
  // SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &sdlOpenGLminor);
  // std::cout << "[INFO] OpenGL from SDL: "
  //           << sdlOpenGLmajor
  //           << "."
  //           << sdlOpenGLminor
  //           << std::endl;

  glViewport(0, 0, windowWidth, windowHeight);

  // setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad
  // Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable
  io.Fonts->AddFontFromFileTTF("assets/fonts/verdana.ttf", 15.0f, NULL, NULL);

  // setup Dear ImGui style
  // ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();
  setImGuiStyle();

  // setup platform/renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version.c_str());

  // colors are set in RGBA, but as float
  ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);

  glClearColor(background.x, background.y, background.z, background.w);
  // --- rendering loop
  bool loop = true;
  while (loop) {
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
        case SDL_WINDOWEVENT_RESIZED:
          windowWidth = event.window.data1;
          windowHeight = event.window.data2;
          // std::cout << "[INFO] Window size: "
          //           << windowWidth
          //           << "x"
          //           << windowHeight
          //           << std::endl;
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
  }

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
