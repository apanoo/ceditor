#include "util.h"
#include "window.hpp"

Window *win;

// the function called by the javascript code
#ifdef EMSCRIPTEN
extern "C" void EMSCRIPTEN_KEEPALIVE toggle_background_color() { 
    if(win != nullptr) win->togglebg();
}
std::function<void()> loop;
void main_loop() { loop(); }
#endif // EMSCRIPTEN


int main()
{
    win = new Window("ceditor", 640, 480);

#ifdef EMSCRIPTEN
    loop = [&]
    {
#else
while(!win->isQuit()) {
#endif // EMSCRIPTEN
    win->update();
#ifdef EMSCRIPTEN
    };
    emscripten_set_main_loop(main_loop, 0, true);
#else
}
#endif
    return EXIT_SUCCESS;
}