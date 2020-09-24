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

#include "2d/gui/functions.h"
#include "entt/systems/velocity.hpp"

int windowWidth = 1280, windowHeight = 720;

int main(int argc, char *argv[]) {
  std::cout << "[" << currentTime(std::chrono::system_clock::now()) << "] "
            << "Start\n- - -\n\n";

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

  SDL_version linked;
  SDL_GetVersion(&linked);
  std::ostringstream linkedVal;
  linkedVal << "Linked with " << std::to_string(linked.major) << "."
            << std::to_string(linked.minor) << "."
            << std::to_string(linked.patch);

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

  glViewport(0, 0, windowWidth, windowHeight);

  // setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.Fonts->AddFontFromFileTTF("assets/fonts/verdana.ttf", 14.0f, NULL, NULL);

  // setup Dear ImGui style
  // ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();
  setImGuiStyle();

  // setup platform/renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version.c_str());

  bool show_demo_window = false;
  bool show_another_window = false;
  // colors are set in RGBA, but as float
  ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);

  entt::registry reg;

  MM::EntityEditor<entt::entity> editor;

  editor.registerComponent<Components::Transform>("Transform");
  editor.registerComponent<Components::Velocity>("Velocity");

  entt::entity e;

  for (size_t i = 0; i < 1; i++) {
    e = reg.create();
    // setup nice initial entity
    {
      // reg.emplace<Components::Transform>(e, 500.f, 500.f);
      // reg.emplace<Components::Velocity>(e, 500.f, 500.f);
      reg.emplace<Components::Transform>(e, float(rand() % 5000) / 10,
                                         float(rand() % 5000) / 10);
      reg.emplace<Components::Velocity>(e, float((rand() % 5000) - 2500) / 10,
                                        float((rand() % 5000) - 2500) / 10);
    }
  }

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

    Systems::Velocity(reg, 1.f / 60.f);

    // start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    // debug draw entities
    {
      auto *dl = ImGui::GetBackgroundDrawList();
      reg.view<Components::Transform>().each(
          [&](auto e, Components::Transform &trans) {
            auto e_int = entt::to_integral(e) + 1;

            // generate color based on id
            auto col = IM_COL32((13 * e_int) % 256, (159 * e_int) % 256,
                                (207 * e_int) % 256, 250);

            dl->AddCircleFilled(ImVec2(trans.x, trans.y), 10.f, col);
          });
    }

    // render editor
    editor.renderSimpleCombo(reg, e);

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
