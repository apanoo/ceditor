#include "logger/log.h"
#include "util.h"
#include "window.hpp"

Window *win;

// the function called by the javascript code
#ifdef EMSCRIPTEN
extern "C" void EMSCRIPTEN_KEEPALIVE toggle_background_color() {
  if (win != nullptr)
    win->togglebg();
}
std::function<void()> loop;
void main_loop() { loop(); }
#endif // EMSCRIPTEN

// application init
// TODO application abstract
int init() {

#if defined(__ANDROID__) || defined(__IPHONEOS__)
  win = new Window("ceditor", 480, 640);
#else
  win = new Window("ceditor", 640, 480);
#endif
  return 1;
}

// application exit
void release() {
  delete (win);
  SDL_Quit();
  SDL_Log("All done.");
}

int main(int argc, char *argv[]) {
  // init logger
  Log::Init();
  // test logger
  HZ_INFO("test logger ");

  if (!init()) {
    SDL_Log("Initialization failed.");
    release();
    return 1;
  }
#ifdef EMSCRIPTEN
  loop = [&] {
#else
  while (!win->isQuit()) {
#endif
    win->update();
#ifdef EMSCRIPTEN
  };
  emscripten_set_main_loop(main_loop, 0, true);
#else
  }
#endif

  // call release
  release();
  return 0;
}
